#include "../../include/Timeline.h"

// public members

Timeline::Timeline(std::unique_ptr<LocusMap> lm) :
    warpMarkerMap(std::move(lm))
{}

float   Timeline::getTimeFromBeat(float beatVal)
{
    return beatVal;
}

float   Timeline::getBeatFromTime(float timeVal)
{
    return timeVal;
}

int     Timeline::insertWarpMarker(float beat, float timestamp)
{
    return timestamp && beat ? 0 : 1;
}

int     Timeline::setEndTempo(float tempo)
{
    return tempo ? 0 : 1;
}
