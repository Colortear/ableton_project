#ifndef LOCUSMAP_H
# define LOCUSMAP_H

# include <array>
# include <map>

namespace locusmap {

struct pole {
    float above;
    float below;
};

pole    make_pole(float f1, float f2);

class LocusMap {
public:
    LocusMap() = default;
    LocusMap(const LocusMap&) = delete;
    LocusMap&   operator=(const LocusMap&) = delete;
    LocusMap(LocusMap&& lm) = default;
    LocusMap&   operator=(LocusMap&& lm) = default;
    ~LocusMap() = default;

    virtual float   upperBoundAboveMap(float) = 0;
    virtual float   lowerBoundAboveMap(float) = 0;
    virtual float   upperBoundBelowMap(float) = 0;
    virtual float   lowerBoundBelowMap(float) = 0;
    virtual int     insertRelationship(const pole&) = 0;
    virtual int     removeIntersecting(const pole&) = 0;
protected:
    virtual std::pair<float, float> getRangeIntersecting(const pole&) = 0;
    virtual bool    isIntersecting(const pole&, const pole&) = 0;
};

};

#endif
