#ifndef MARKERMAP_H
# define MARKERMAP_H

# include "LocusMap.h"
# include "WarpMarker.h"
# include <memory>

class MarkerMap final : public locusmap::LocusMap {
public:
    using marker_map = std::map<double, std::shared_ptr<WarpMarker>>;
    using map_iter = marker_map::iterator;

    MarkerMap() = default;
    MarkerMap(MarkerMap&& mm) = default;
    MarkerMap&  operator=(MarkerMap&& mm) = default;
    ~MarkerMap() = default;

    locusmap::option_pole   upperBoundAboveMap(const double point) const override;
    locusmap::option_pole   lowerBoundAboveMap(const double point) const override;
    locusmap::option_pole   upperBoundBelowMap(const double point) const override;
    locusmap::option_pole   lowerBoundBelowMap(const double point) const override;
    void    insertRelationship(const double beat, const double time) override;
    size_t  aSize() const override;
    size_t  bSize() const override;
private:
    void    removeIntersecting(const locusmap::pole& marker) override;
    void    removeFromBeat(const locusmap::pole& marker);
    void    removeFromTime(const locusmap::pole& marker);
    bool    isIntersecting(const locusmap::pole& m1, const locusmap::pole& m2) const override;

    marker_map  _beatMap;
    marker_map  _timeMap;
};

#endif
