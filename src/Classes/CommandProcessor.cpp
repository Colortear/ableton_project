#include "../../include/Command.h"
#include <string>

using namespace command;

template <typename CommandType, typename T>
void CommandProcessor::registerCommand(std::string name, T& arg)
{
    this->_commands.emplace(name, std::make_unique<CommandType>(arg));
}

int CommandProcessor::executeCommand(commandList& std::vector<string>)
{
}
