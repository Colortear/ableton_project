#ifndef COMMAND_H
# define COMMAND_H

# include <vector>
# include <memory>
# include <unordered_map>
# include <string>
# include "ITimeline.h"
# include "utility.h"

// There would normally be an implementation of input error handling here
// but the prompt explicitly stated the input would always be given in correct form

using commandList = std::vector<std::string>;
namespace command {

class Command {
public:
    virtual ~Command() = default;

    virtual int     invoke() = 0;
    virtual void    assignInput(const commandList& args) = 0;
    virtual size_t  acceptedArgCount() const = 0;
};

class InsertWarpMarker final : public Command {
public:
    InsertWarpMarker(timeline::ITimeline& timeline);

    int     invoke() override;
    void    assignInput(const commandList& args) override;
    size_t  acceptedArgCount() const override;
    
private:
    timeline::ITimeline&    _timeline;
    double                  _beat;
    double                  _timestamp;
    size_t                  _argCount;
};

class DefineEndTempo final : public Command {
public:
    DefineEndTempo(timeline::ITimeline& timeline);

    int     invoke() override;
    void    assignInput(const commandList& args) override;
    size_t  acceptedArgCount() const override;
private:
    timeline::ITimeline&    _timeline;
    double                  _tempo;
    size_t                  _argCount;
};

class ConvertTimeToBeat final : public Command {
public:
    ConvertTimeToBeat(timeline::ITimeline& timeline);

    int     invoke() override;
    void    assignInput(const commandList& args) override;
    size_t  acceptedArgCount() const override;
private:
    timeline::ITimeline&    _timeline;
    double                  _time;
    size_t                  _argCount;
};

class ConvertBeatToTime final : public Command {
public:
    ConvertBeatToTime(timeline::ITimeline& timeline);

    int     invoke() override;
    void    assignInput(const commandList& args) override;
    size_t  acceptedArgCount() const override;
private:
    timeline::ITimeline&    _timeline;
    double                  _beat;
    size_t                  _argCount;
};

class CommandProcessor {
public:
    CommandProcessor() = default;
    CommandProcessor(const CommandProcessor&) = delete;
    CommandProcessor operator=(const CommandProcessor&) = delete;
    ~CommandProcessor() = default;

    template <typename C, typename ...Refs>
    void    registerCommand(std::string name, Refs&&... refs);
    int     executeCommand(const utility::CommandData& cd);
private:
    std::unordered_map<std::string, std::unique_ptr<Command>>  _commands;
};

void    registerCommands(CommandProcessor& cp, timeline::ITimeline& timeline);

#include "registerCommand.tpp"

}

#endif
