#include <sstream>
#include "../include/utility.h"

namespace utility {

strings splitStr(std::string line)
{
    std::stringstream   ss(line);
    std::string         tmp;
    strings             commands;

    while (getline(ss, tmp, ' '))
        commands.emplace_back(tmp);
    return commands;
}

void    CommandData::fillData(strings line)
{
    if (line.size() > 1) {
        command = *line.begin();
        args = strings(line.begin()+1, line.end());
    }
}

}
