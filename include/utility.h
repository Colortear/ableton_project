#ifndef UTILITY_H
# define UTILITY_H

# include <vector>
# include <string>

namespace utility {

using strings = std::vector<std::string>;

strings splitStr(std::string line);

class CommandData {
public:
    std::string                 command;
    std::vector<std::string>    args;
    void    fillData(std::vector<std::string> line);
};

};

#endif
