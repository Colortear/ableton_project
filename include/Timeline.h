#ifndef TIMELINE_H
# define TIMELINE_H

# include <map>
# include <memory>
# include <MarkerMap.h>
# include <ITimeline.h>

namespace timeline {

class Timeline final : public ITimeline {
public:
    using timelineMap = std::unique_ptr<locusmap::LocusMap>;

    Timeline(timelineMap lm);
    
    void    insertWarpMarker(const double beat, const double timestamp) override;
    void    setEndTempo(const double tempo) override;
    double  getBeatFromTime(const double timeVal) const override;
    double  getTimeFromBeat(const double beatVal) const override;
private:
    double  calculateRelationship(const double inc, const range& r1, const range& r2) const override;
    double  calculateTimeByTempo(const double inc, const locusmap::pole& lower) const override;
    double  calculateBeatByTempo(const double inc, const locusmap::pole& lower) const override;

    timelineMap _warpMarkerMap;
    double      _endTempo;
};

}

#endif
