#ifndef COMMAND_H
# define COMMAND_H

# include <vector>
# include <memory>
# include <map>

using commandList = std::vector<std::string>;
namespace command {

void    registerCommands();

class CommandProcessor {
public:
    CommandProcessor() = default;
    CommandProcessor(const CommandProcessor&) = delete;
    CommandProcessor operator=(const CommandProcessor&) = delete;
    ~CommandProcessor() = default;

    template <typename CommandType, typename T>
    void    registerCommand(std::string name, T& arg);
    int     executeCommand(commandList& c);
private:
    std::map<std::unique_ptr<Command>>  _commands;
};

class Command {
public:
    Command(const Command&) = delete;
    Command& operator=(const Command&) = delete;
    ~Command() = default;

    virtual int invoke() = 0;
};

class InsertWarpMarker : public Command {
public:
    InsertWarpMarker(Timeline& timeline);

    int invoke();
private:
    Timeline&   _timeline;
    float       _beat;
    float       _timestamp;
};

class DefineEndTempo : public Command {
public:
    DefineEndTempo(Timeline& timeline);
    int invoke();
private:
    Timeline&   _timeline;
    float       _tempo;
};

class ConvertTimeToBeat : public Command {
public:
    ConvertTimeToBeat(Timeline& timeline);
    int invoke();
private:
    Timeline&   _timeline;
    float       _time;
};

class ConvertBeatToTime : public Command {
public:
    ConvertBeatToTime(Timeline& timeline, commandList& commands);
    int invoke();
private:
    Timeline&   _timeline;
    float       _beat;
};

}

#endif
