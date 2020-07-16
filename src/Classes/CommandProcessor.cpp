#include "../../include/Command.h"

#include <iostream>

using namespace utility;

namespace command {

int CommandProcessor::executeCommand(const CommandData& cd)
{
    if (auto it = _commands.find(cd.command); it != _commands.end()) {
        auto& command = it->second;
        if (cd.args.size() == command->acceptedArgCount()) {
            command->assignInput(cd.args);
            return command->invoke();
        }
    }
    return 1;
}

}
