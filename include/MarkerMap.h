#ifndef MARKERMAP_H
# define MARKERMAP_H

# include "LocusMap.h"
# include "WarpMarker.h"

class MarkerMap : public LocusMap {
public:
    LocusMap(const LocusMap&& lm);
    LocusMap&   operator=(const LocusMap&& lm);

    float   upperBoundAboveMap(float point);
    float   lowerBoundAboveMap(float point);
    float   upperBoundBelowMap(float point);
    float   lowerBoundBelowMap(float point);
    int     insertRelationship(locusmap::pole pole);
    int     removeIntersecting(locusmap::pole pole);
private:
    std::pair<float, float> getRangeIntersecting(locusmap::pole marker);
    bool    isIntersecting(locusmap::pole marker, locusmap::pole marker);
    std::map<float, std::shared_ptr<WarpMarker>> _beatMap;
    std::map<float, std::shared_ptr<WarpMarker>> _timeMap;
};

#endif
