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
    virtual LocusMap(const LocusMap&) = delete;
    virtual LocusMap    operator=(const LocusMap&) = delete;
    virtual LocusMap(const LocusMap&&) = default;
    virtual LocusMap    operator=(const LocusMap&&) = default;
    virtual ~LocusMap() = default;

    virtual float   upperBoundAboveMap(float) = 0;
    virtual float   lowerBoundAboveMap(float) = 0;
    virtual float   upperBoundBelowMap(float) = 0;
    virtual float   lowerBoundBelowMap(float) = 0;
    virtual int     insertRelationship(pole) = 0;
    virtual int     removeIntersecting(pole) = 0;
protected:
    virtual std::pair<float, float> getRangeIntersecting(pole) = 0;
    virtual bool    isIntersecting(pole, pole) = 0;
};

};

#endif
