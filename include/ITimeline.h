#ifndef ITIMELINE_H
# define ITIMELINE_H

# include "LocusMap.h"

namespace timeline {

struct range {
    double  lower;
    double  upper;
};

class ITimeline {
public:
    virtual ~ITimeline() = default;
    virtual void    insertWarpMarker(const double, const double) = 0;
    virtual void    setEndTempo(const double) = 0;
    virtual double  getBeatFromTime(const double) const = 0;
    virtual double  getTimeFromBeat(const double) const = 0;
protected:
    virtual double  calculateRelationship(const double, const range&, const range&) const = 0;
    virtual double  calculateTimeByTempo(const double, const locusmap::pole&) const = 0;
    virtual double  calculateBeatByTempo(const double, const locusmap::pole&) const = 0;
};

}

#endif
