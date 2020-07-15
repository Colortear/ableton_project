#include "../../include/MarkerMap.h"
#include "../../include/utility.h"
#include <iostream>

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
        if (auto it = _beatMap.lower_bound(point); it != _beatMap.begin()) {
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
        if (auto it = _timeMap.lower_bound(point); it != _timeMap.begin()) {
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
    _beatMap[above] = wm;
    _timeMap[below] = wmcopy;
}

size_t  MarkerMap::aSize() const
{
    return _beatMap.size();
}

size_t  MarkerMap::bSize() const
{
    return _timeMap.size();
}

void    MarkerMap::removeIntersecting(const pole& marker)
{
    removeFromBeat(marker);
    removeFromTime(marker);
}

void    MarkerMap::removeFromBeat(const pole& marker)
{
    auto [beat, time] = marker;
    auto it = _beatMap.lower_bound(beat);
    auto beatFirst = it;

    for (; _beatMap.size(); it++) {
        if (it != _beatMap.end() &&
                isIntersecting({beat, time}, {it->first, it->second->time()}))
            continue ;
        _beatMap.erase(beatFirst, it);
        return ;
    }
}

void    MarkerMap::removeFromTime(const pole& marker)
{
    auto [beat, time] = marker;
    auto it = _timeMap.lower_bound(time);
    auto timeFirst = it;

    for (; _timeMap.size(); it++) {
        if (it != _timeMap.end() &&
                isIntersecting({beat, time}, {it->second->beat(), it->first}))
            continue ;
        _timeMap.erase(timeFirst, it);
        return ;
    }
}

bool    isBefore(const pole& m1, const pole& m2)
{
    return m2.above <= m1.above || m2.below <= m1.below;
}

bool    MarkerMap::isIntersecting(const pole& m1, const pole& m2) const
{
    auto aboveDist = m2.above - m1.above;
    auto belowDist = m2.below - m1.below;

    return isBefore(m1, m2) &&
        ((aboveDist <= 0 && belowDist >= 0) ||
         (aboveDist >= 0 && belowDist <= 0));
}
