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
 *      In order to detect the number of intersecting lines, following logic should be sufficient:
 *          1. find the minimum end of the pole marker that is being inserted.
 *          2. starting from it's placement in the map, iterate forward.
 *          3. for every visited entry where the diametric end of the pole is less than
 *              the corresponding end of the pole to be inserted, remove that pole.
 *          4. repeat 2 if 3 is true, else end the process and insert the pole into the map.
 *
 * end_tempo <value>:
 *      Simply store the value in the corresponding container.
 *
 * s2b <sample time>:
 *      In order to find the interpolation a given point on the sample line we find the markers that
 *      delimit the area that the point is contained. The the lower and upper bound of that signify
 *      the markers closest to the provided sample time are used to get the distance between the two.
 *      The corresponding side can be found by finding the distance between sample times in the upper
 *      and lower bounds (markers) and then finding the distance between the corresponding diametric
 *      poles. The sample distance is then divided by the beat distance (opposing end). The resulting
 *      ratio and the original value to be applied (input) are factors for the product: the 
 *      corresponding beat time. in other words:
 *          Where s = sample time (input), Us = sample upper bound, Ls = sample lower bound,
 *          Ub = beat upper bound, Lb = beat lower bound:
 *
 *                          Us - Ls
 *                  b = s * -------
 *                          Ub - Lb
 *
 *          and b is now the corresponding time to s per the relationship of the markers.
 *
 * b2s <beat time>:
 *      calculating the corresponding value of a given beat value is as simple as reversing the
 *      values in the previous calculation where the beat distance is now divided by the sample
 *      distance:
 *
 *                          Ub - Lb
 *                  s = b * -------
 *                          Us - Ls
 *
 * There are two special cases regarding the number of markers currently in the map. If the map is
 * empty there is no special characteristic of the values and the rate between the two is constant,
 * or 1/1. In the instance that there is only one marker, the marker is not contingent upon a
 * correlative marker since in either direction is ∞ or 0, and since ∞/∞ and 0/0 is undefined
 * a query under this state must be treated specially. if end_tempo is not provided any query past
 * the last marker would be undefined. per the document there will always be an end_tempo and a
 * single marker. Therefore if the map is populated with only a single marker then we will treat all
 * values at the rate of end_tempo.
 *
 * to calculate the relationship between the first marker and 0 in instance that there are multiple
 * markers, that first segment is treated as an extension of the segment demarcated by the first
 * and second markers.
 */

class Timeline {
private:
    LocusMap    warpMarkerMap;
    float       _endTempo;

    slice   getSliceFromBeat(float beatVal);
    slice   getSliceFromTime(float timeVal);
    bool    isIntersecting(WarpMarker& wm);
    // use remove if with erase and inline the predicate
public:
    Timeline() = default;

    int     insertWarpMarker(float beat, float timestamp); // marker <beat time> <sample time>
    int     setEndTempo(float tempo); // end_tempo <value>
    float   getBeatFromTime(float timeVal); // s2b <sample time>
    float   getTimeFromBeat(float beatVal); // b2s <beat time>
};

#endif
