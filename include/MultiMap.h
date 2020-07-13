#ifndef LOCUSMAP_H
# define LOCUSMAP_H

# include <array>
# include <map>

template <class C, class E>
class LocusMap {
public:
    LocusMap(std::array<std::pair<enum E, std::function<
    LocusMap(const LocusMap& mm) = delete;
    LocusMap    operator=(const LocusMap& mm) = delete;
    LocusMap(const LocusMap&& mm) = default;
    LocusMap    operator=(const LocusMap&& mm) = default;
private:
    std::array<std::map<int, C>
};

#endif
