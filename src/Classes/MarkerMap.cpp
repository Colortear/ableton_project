#include "../../include/MarkerMap.h"
#include "../../include/utility.h"

using namespace locusmap;
using namespace utility;

option_pole   MarkerMap::upperBoundAboveMap(double point) const
{
    if (auto it = _beatMap.lower_bound(point); it != _beatMap.end())
        return option_pole({it->first, it->second->time()});
    return std::nullopt;
}

option_pole MarkerMap::lowerBoundAboveMap(double point) const
{
    if (_beatMap.size()) {
        if (auto it = _beatMap.lower_bound(point);
                it != _beatMap.end() && it != _beatMap.begin()) {
            it--;
            return option_pole({it->first, it->second->time()});
        }
    }
    return std::nullopt;
}

option_pole   MarkerMap::upperBoundBelowMap(double point) const
{
    if (auto it = _timeMap.lower_bound(point); it != _timeMap.end())
        return option_pole({it->second->beat(), it->first});
    return std::nullopt;
}

option_pole MarkerMap::lowerBoundBelowMap(double point) const
{
    if (_timeMap.size()) {
        if (auto it = _timeMap.lower_bound(point);
                it != _timeMap.end() && it != _timeMap.begin()) {
            it--;
            return option_pole({it->second->beat(), it->first});
        }
    }
    return std::nullopt;
}

void    MarkerMap::insertRelationship(const double above, const double below)
{
    auto wm = std::make_shared<WarpMarker>(above, below);
    auto wmcopy = wm;

    removeIntersecting(pole {above, below});
    _beatMap.emplace(above, wm);
    _timeMap.emplace(below, wmcopy);
}

size_t  MarkerMap::size() const
{
    return _timeMap.size();
}

void    MarkerMap::eraseMarkerByBeat(map_iter mi, double timeKey) 
{
    _beatMap.erase(mi);
    _timeMap.erase(timeKey);
}

void    MarkerMap::eraseMarkerByTime(map_iter mi, double beatKey)
{
    _timeMap.erase(mi);
    _beatMap.erase(beatKey);
}

void    MarkerMap::removeFromBeat(const pole& marker)
{
    auto [beat, time] = marker;

    for (auto it = _beatMap.lower_bound(beat); it != _beatMap.end(); it++) {
        if (it->first > beat && it->second->time() > time)
            break ;
        if (isIntersecting(pole {beat, time}, pole {it->first, it->second->time()}))
            eraseMarkerByTime(it, it->second->time());
    }
}

void    MarkerMap::removeFromTime(const pole& marker)
{
    auto [beat, time] = marker;

    for (auto it = _timeMap.lower_bound(time); it != _timeMap.end(); it++) {
        if (it->first > time && it->second->time() > beat)
            break ;
        if (isIntersecting(pole {beat, time}, pole {it->second->beat(), it->first}))
            eraseMarkerByTime(it, it->second->beat());
    }
}

void    MarkerMap::removeIntersecting(const pole& marker)
{
    removeFromBeat(marker);
    removeFromTime(marker);
}

bool    MarkerMap::isIntersecting(const pole& m1, const pole& m2) const
{
    auto above = m2.above - m1.above;
    auto below = m2.below - m1.below;
    return (above <= 0 && below >= 0) || (above >= 0 && below <= 0);
}
