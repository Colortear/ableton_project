#include <iostream>
#include "../include/warpedrecord.h"

using namespace utility;
using namespace command;
using namespace timeline;

int main(void)
{
    std::string         line;
    Timeline            timeline { std::make_unique<MarkerMap>() };
    CommandData         cd;
    CommandProcessor    cp;

    registerCommands(cp, timeline);
    while (getline(std::cin, line)) { 
        cd.fillData(splitStr(line));
        cp.executeCommand(cd);
    }
    return 0;
}
