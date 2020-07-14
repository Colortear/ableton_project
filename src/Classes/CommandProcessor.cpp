#include "../../include/Command.h"

#include <iostream>

using namespace utility;

namespace command {

int CommandProcessor::executeCommand(const CommandData& cd)
{
    if (auto it = _commands.find(cd.command);
            it != _commands.end() && cd.args.size()) {
        auto& command = it->second;
        command->assignInput(cd.args);
        return command->invoke();
    }
    return 1;
}

}
