#ifndef COMMAND_H
# define COMMAND_H

# include <vector>
# include <memory>
# include <unordered_map>
# include <string>
# include "Timeline.h"
# include "utility.h"

using commandList = std::vector<std::string>;
namespace command {

class Command {
public:
    virtual ~Command() = default;

    virtual int     invoke() = 0;
    virtual void    assignInput(const commandList& args) = 0;
};

class InsertWarpMarker final : public Command {
public:
    InsertWarpMarker(Timeline& timeline);

    int     invoke() override;
    void    assignInput(const commandList& args) override;
private:
    Timeline&   _timeline;
    float       _beat;
    float       _timestamp;
};

class DefineEndTempo final : public Command {
public:
    DefineEndTempo(Timeline& timeline);

    int     invoke() override;
    void    assignInput(const commandList& args) override;
private:
    Timeline&   _timeline;
    float       _tempo;
};

class ConvertTimeToBeat final : public Command {
public:
    ConvertTimeToBeat(Timeline& timeline);

    int     invoke() override;
    void    assignInput(const commandList& args) override;
private:
    Timeline&   _timeline;
    float       _time;
};

class ConvertBeatToTime final : public Command {
public:
    ConvertBeatToTime(Timeline& timeline);

    int     invoke() override;
    void    assignInput(const commandList& args) override;
private:
    Timeline&   _timeline;
    float       _beat;
};

class CommandProcessor {
public:
    CommandProcessor() = default;
    CommandProcessor(const CommandProcessor&) = delete;
    CommandProcessor operator=(const CommandProcessor&) = delete;
    ~CommandProcessor() = default;

    template <typename C, typename ...Refs>
    void    registerCommand(std::string name, Refs&... refs);
    int     executeCommand(const utility::CommandData& cd);
private:
    std::unordered_map<std::string, std::unique_ptr<Command>>  _commands;
};

void    registerCommands(CommandProcessor& cp, Timeline& timeline);

#include "registerCommand.tpp"

}

#endif