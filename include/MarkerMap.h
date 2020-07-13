#ifndef MARKERMAP_H
# define MARKERMAP_H

# include "LocusMap.h"
# include "WarpMarker.h"
# include <memory>

using namespace locusmap;

class MarkerMap final : public LocusMap {
public:
    MarkerMap() = default;
    MarkerMap(MarkerMap&& mm);
    MarkerMap&  operator=(MarkerMap&& mm);
    ~MarkerMap() = default;

    float   upperBoundAboveMap(float point) override;
    float   lowerBoundAboveMap(float point) override;
    float   upperBoundBelowMap(float point) override;
    float   lowerBoundBelowMap(float point) override;
    int     insertRelationship(const pole& pole) override;
    int     removeIntersecting(const pole& pole) override;
private:
    std::pair<float, float> getRangeIntersecting(const pole& marker) override;
    bool    isIntersecting(const pole& dependent, const pole& independent) override;

    std::map<float, WarpMarker> _map;
};

#endif
