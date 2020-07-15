#include "../../include/Timeline.h"
#include <cmath>

using namespace locusmap;

namespace timeline {

Timeline::Timeline(timelineMap lm) :
    _warpMarkerMap(std::move(lm)),
    _endTempo(1.0)
{}

void    Timeline::insertWarpMarker(const double beat, const double timestamp)
{
    _warpMarkerMap->insertRelationship(beat, timestamp);
}

void    Timeline::setEndTempo(const double tempo)
{
    _endTempo = tempo;
}

double  Timeline::getNextRatioAbove(const pole& lower) const
{
    auto [above, below] = lower;

    try {
        auto upper = _warpMarkerMap->upperBoundAboveMap(std::nextafter(above, above+1.0));

        if (!upper)
            throw;
        return (upper->below - below) / (upper->above - above);
    }
    catch (std::exception& e) {
        return 1.0;
    }
}

double  Timeline::getNextRatioBelow(const pole& lower) const
{
    auto [above, below] = lower;

    try {
        auto upper = _warpMarkerMap->upperBoundBelowMap(std::nextafter(below, below+1.0));

        if (!upper)
            throw ;
        return (upper->above - above) / (upper->below - below);
    }
    catch (std::exception& e) {
        return 1.0;
    }
}

double  Timeline::getTimeFromBeat(const double beatVal) const
{
    range   beat_r, time_r;
    auto    upperBound = _warpMarkerMap->upperBoundAboveMap(beatVal);
    auto    lowerBound = _warpMarkerMap->lowerBoundAboveMap(beatVal);

    if (upperBound && lowerBound) {
        beat_r = range {lowerBound->above, upperBound->above};
        time_r = range {lowerBound->below, upperBound->below};
        return calculateRelationship(beatVal, beat_r, time_r);
    }
    else if (!upperBound || (!lowerBound && _warpMarkerMap->aSize() == 1))
        return calculateTimeByTempo(beatVal, *lowerBound);
    else if (!lowerBound && upperBound) {
        return upperBound->below - (getNextRatioAbove(*upperBound) * (upperBound->above - beatVal));
    }
    return beatVal;
}

double  Timeline::getBeatFromTime(const double timeVal) const
{
    range   beat_r, time_r;
    auto    upperBound = _warpMarkerMap->upperBoundBelowMap(timeVal);
    auto    lowerBound = _warpMarkerMap->lowerBoundBelowMap(timeVal);

    if (upperBound && lowerBound) {
        beat_r = range {lowerBound->above, upperBound->above};
        time_r = range {lowerBound->below, upperBound->below};
        return calculateRelationship(timeVal, time_r, beat_r);
    }
    else if (!upperBound || (!lowerBound && _warpMarkerMap->bSize() == 1))
        return calculateBeatByTempo(timeVal, *lowerBound);
    else if (!lowerBound && upperBound)
        return upperBound->above - (getNextRatioBelow(*upperBound) * (upperBound->below - timeVal));
    return timeVal;
}

double  Timeline::calculateRelationship(const double inc, const range& r1, const range& r2) const
{
    auto ratio = ((inc - r1.lower) / (r1.upper - r1.lower));
    auto other_distance = r2.upper - r2.lower;

    return r2.lower + (ratio * other_distance);
}

double  Timeline::calculateTimeByTempo(const double inc, const pole& lower) const
{
    return lower.below + ((inc - lower.above) / _endTempo);
}

double  Timeline::calculateBeatByTempo(const double inc, const pole& lower) const
{
    return ((inc - lower.below) * _endTempo) + lower.above;
}

}
