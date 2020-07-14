#include "../../include/Timeline.h"

// public members

using namespace locusmap;

Timeline::Timeline(std::unique_ptr<LocusMap> lm) :
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

double  Timeline::getTimeFromBeat(const double beatVal) const
{
    range   beat_r, time_r;
    auto    upperBound = _warpMarkerMap->upperBoundAboveMap(beatVal);
    auto    lowerBound = _warpMarkerMap->lowerBoundAboveMap(beatVal);

    if (upperBound && lowerBound) {
            beat_r = range {lowerBound->above, upperBound->above};
            time_r = range {lowerBound->below, upperBound->below};
            return calculateRelationship(beatVal, time_r, beat_r);
        }
        else if (!upperBound || (!lowerBound && _warpMarkerMap->size() == 1))
            return calculateTimeByTempo(beatVal, *lowerBound);
        else if (!lowerBound)
            getTimeFromBeat(upperBound->above);
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
        return calculateRelationship(timeVal, beat_r, time_r);
    }
    else if ((!lowerBound && _warpMarkerMap->size() == 1) || !upperBound)
        return calculateBeatByTempo(timeVal, *lowerBound);
    else if (!lowerBound)
        return getBeatFromTime(upperBound->below);
    return timeVal;
}

double  Timeline::calculateRelationship(const double inc, const range& r1, const range& r2) const
{
    return inc * ((r1.upper - r1.lower) / (r2.upper - r2.lower));
}

double  Timeline::calculateTimeByTempo(const double inc, const pole& lower) const
{
    return lower.below + ((inc - lower.above) / _endTempo);
}

double  Timeline::calculateBeatByTempo(const double inc, const pole& lower) const
{
    return ((inc - lower.below) * _endTempo) + lower.above;
}
