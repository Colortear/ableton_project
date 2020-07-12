#include <iostream>
#include "../include/warpedrecord.h"

using namespace utility;

int main(void)
{
    std::vector<std::string>    tokline;
    std::string                 line;
    Timeline                    timeline;
    CommandData                 cd;
    command::CommandProcessor   cp;

    command::registerCommands(cp, timeline);
    while (getline(std::cin, line)) {
        auto tokline = splitStr(line);
        cd.fillData(tokline);
        cp.executeCommand(cd);
    }
    return 0;
}
