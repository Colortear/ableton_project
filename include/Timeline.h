#ifndef TIMELINE_H
# define TIMELINE_H

# include <map>
# include <memory>
# include "MarkerMap.h"

/* Operations:
 * marker <beat time> <sample time>:
 *      When a marker is place into the map container the span between the two may overlap
 *      one or more other markers. I have decided that the natural solution to overlap is to
 *      remove the existing markers that have been interrupted by the new marker given that
 *      the new marker is within the reasonable limits of our data primitives and non-negative.
 *      The reason is that I cannot think of a reasonable way of handling intersecting relationships
 *      between the lines. using the formula provided below it would result in negative values.
 *
 * end_tempo <value>:
 *      Simply store the value in the corresponding container.
 *
 * s2b <sample time>:
 *      In order to find the interpolation a point on the sample line, find the markers that delimit
 *      the area that the point is contained. The the lower and upper bound of the area signify
 *      the markers closest to the provided sample time are used to get the distance between the two.
 *      The corresponding side can be found by finding the distance between sample times in the upper
 *      and lower bounds (markers) and then finding the distance between the corresponding diametric
 *      poles. The beat distance is then divided by the sample distance (opposing end). The resulting
 *      ratio and the original value to be applied (input) are multipled for the corresponding
 *      beat time. In other words:
 *          Where s = sample time (input), Us = sample upper bound, Ls = sample lower bound,
 *          Ub = beat upper bound, Lb = beat lower bound:
 *
 *                          Ub - Lb
 *                  b = s * -------
 *                          Us - Ls
 *
 *          and b is now the corresponding time to s per the relationship of the markers.
 *
 * b2s <beat time>:
 *      calculating the corresponding value of a given beat value is as simple as reversing the
 *      values in the previous calculation where the sample distance is now divided by the beat
 *      distance:
 *
 *                          Us - Ls
 *                  s = b * -------
 *                          Ub - Lb
 *
 * There are two special cases regarding the number of markers currently in the map. If the map is
 * empty there is no special characteristic of the values and the rate between the two is constant,
 * or 1/1. In the instance that there is only one marker, the marker is not contingent upon a
 * correlative marker since in either direction is ∞ or 0, and since ∞/∞ and 0/0 is undefined
 * a query under this state must be treated specially. If end_tempo is not provided, any query past
 * the last marker would be undefined. per the document there will always be an end_tempo and a
 * single marker. Therefore if the map is populated with only a single marker then all values will
 * be processed at the rate of end_tempo. The relationships past the final can be calculated for
 * given a sample value where tempo is beats per one second (sample unit):
 *
 *                  b = ((s - Ls) * tempo) + Lb
 *
 * and to find the converse:
 *
 *                            b - Lb
 *                  s = Ls + --------
 *                            tempo
 *
 * to calculate the relationship between the first marker and 0 in instance that there are multiple
 * markers, that first segment is treated as an extension of the segment demarcated by the first
 * and second markers.
 */

struct range {
    double  lower;
    double  upper;
};

class Timeline {
public:
    using timelineMap = std::unique_ptr<locusmap::LocusMap>;

    Timeline(std::unique_ptr<locusmap::LocusMap> lm);
    
    void    insertWarpMarker(const double beat, const double timestamp);
    void    setEndTempo(const double tempo);
    double  getBeatFromTime(const double timeVal) const;
    double  getTimeFromBeat(const double beatVal) const;
private:
    double  calculateRelationship(const double inc, const range& r1, const range& r2) const;
    double  calculateTimeByTempo(const double inc, const locusmap::pole& lower) const;
    double  calculateBeatByTempo(const double inc, const locusmap::pole& lower) const;

    timelineMap _warpMarkerMap;
    double      _endTempo;
};

#endif
