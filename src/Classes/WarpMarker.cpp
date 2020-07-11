#include "../../include/WarpMarker.h"

WarpMarker::WarpMarker(float beat, float timestamp) :
    _beat(beat),
    _timestamp(timestamp)
{}

WarpMarker::WarpMarker(WarpMarker&& wm) :
    _beat(wm.beat()),
    _timestamp(wm.time())
{}

inline
float   WarpMarker::getTempo() const
{
    return this->beat() / this->time();
}

float   WarpMarker::beat() const { return _beat; }

float   WarpMarker::time() const { return _timestamp; }
