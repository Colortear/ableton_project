#include "../include/utility.h"

#include <sstream>

using strings = std::vector<std::string>;

inline
strings utility::splitStr(std::string line)
{
    std::stringstream   ss(line);
    std::string         tmp;
    strings             commands;

    while (getline(ss, tmp, ' '))
        commands.emplace_back(tmp);
    return commands;
}
