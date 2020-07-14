#ifndef UTILITY_H
# define UTILITY_H

# include <vector>
# include <string>
# include <optional>

namespace utility {

using strings = std::vector<std::string>;

strings splitStr(std::string line);

template <typename O>
std::optional<O>    make_optional_if(bool argument, O value);

class CommandData {
public:
    std::string                 command;
    std::vector<std::string>    args;
    void    fillData(std::vector<std::string> line);
};

# include "utility.tpp"

};

#endif
