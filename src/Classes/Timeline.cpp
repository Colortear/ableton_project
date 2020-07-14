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
    auto    upper = _warpMarkerMap->upperBoundAboveMap(beatVal);
    auto    lower = _warpMarkerMap->lowerBoundAboveMap(beatVal);

    if (upper || lower) {
        if (upper && lower) {
            beat_r = range {lower->above, upper->above};
            time_r = range {lower->below, upper->below};
            return calculateRelationship(beatVal, time_r, beat_r);
        }
        else if (!upper || (!lower && _warpMarkerMap->size() == 1))
            return deduceTimeByTempo(beatVal, *lower);
        else if (!lower)
            ;
    }
    return beatVal;
}

double  Timeline::getBeatFromTime(const double timeVal) const
{
    return timeVal;
}
