#ifndef LOCUSMAP_H
# define LOCUSMAP_H

# include <array>
# include <map>
# include <optional>

namespace locusmap {

struct pole {
    double above;
    double below;
};

using option_pole = std::optional<pole>;

class LocusMap {
public:
    LocusMap() = default;
    LocusMap(const LocusMap&) = delete;
    LocusMap&   operator=(const LocusMap&) = delete;
    LocusMap(LocusMap&& lm) = default;
    LocusMap&   operator=(LocusMap&& lm) = default;
    virtual ~LocusMap() = default;

    virtual option_pole upperBoundAboveMap(double) const = 0;
    virtual option_pole lowerBoundAboveMap(double) const = 0;
    virtual option_pole upperBoundBelowMap(double) const = 0;
    virtual option_pole lowerBoundBelowMap(double) const = 0;
    virtual void    insertRelationship(const double, const double) = 0;
    virtual size_t  aSize() const = 0;
    virtual size_t  bSize() const = 0;
protected:
    virtual void    removeIntersecting(const pole&) = 0;
    virtual bool    isIntersecting(const pole&, const pole&) const = 0;
};

};

#endif
