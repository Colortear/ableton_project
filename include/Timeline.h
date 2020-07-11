#ifndef TIMLINE_H
# define TIMELINE_H

# include <map>
# include <memory>
# include "WarpMarker.h"

using slice = std::pair<std::shared_ptr<WarpMarker>, std::shared_ptr<WarpMarker>>;

class Timeline {
private:
    // create multi map class in place of this to control insertion and deletion
    // use emplace
    std::map<float, std::shared_ptr<WarpMarker>> _beatMap;
    std::map<float, std::shared_ptr<WarpMarker>> _timeMap;
    float                                        _endTempo;

    slice   getSliceFromBeat(float beatVal);
    slice   getSliceFromTime(float timeVal);
    void    removeIntersecting();
    bool    isIntersecting(WarpMarker& wm);
    // use remove if with erase and inline the predicate
public:
    float   getTimeFromBeat(float beatVal);
    float   getBeatFromTime(float timeVal);
    int     insertWarpMarker(float beat, float timestamp);
    int     setEndTempo(float tempo);
};

#endif
