#include "../../include/Command.h"
#include <iostream>

using namespace timeline;

namespace command {

InsertWarpMarker::InsertWarpMarker(ITimeline& timeline) :
    _timeline(timeline),
    _beat(0.0),
    _timestamp(0.0),
    _argCount(2)
{}

int InsertWarpMarker::invoke()
{
    _timeline.insertWarpMarker(_beat, _timestamp);
    return 0;
}

void    InsertWarpMarker::assignInput(const commandList& args)
{
    _beat = std::stof(args[0]);
    _timestamp = std::stof(args[1]);
}

size_t  InsertWarpMarker::acceptedArgCount() const { return _argCount; }

DefineEndTempo::DefineEndTempo(ITimeline& timeline) :
    _timeline(timeline),
    _tempo(0.0),
    _argCount(1)
{}

int DefineEndTempo::invoke()
{
    _timeline.setEndTempo(_tempo);
    return 0;
}

void    DefineEndTempo::assignInput(const commandList& args)
{
    _tempo = std::stof(args[0]);
}

size_t  DefineEndTempo::acceptedArgCount() const { return _argCount; }

ConvertTimeToBeat::ConvertTimeToBeat(ITimeline& timeline) :
    _timeline(timeline),
    _time(0.0),
    _argCount(1)
{}

int ConvertTimeToBeat::invoke()
{
    std::cout << _timeline.getBeatFromTime(_time) << std::endl;
    return 0;
}

void    ConvertTimeToBeat::assignInput(const commandList& args)
{
    _time = std::stod(args[0]);
}

size_t  ConvertTimeToBeat::acceptedArgCount() const { return _argCount; }

ConvertBeatToTime::ConvertBeatToTime(ITimeline& timeline) :
    _timeline(timeline),
    _beat(0.0),
    _argCount(1)
{}

int ConvertBeatToTime::invoke()
{
    std::cout << _timeline.getTimeFromBeat(_beat) << std::endl;
    return 0;
}

void    ConvertBeatToTime::assignInput(const commandList& args)
{
    _beat = std::stod(args[0]);
}

size_t  ConvertBeatToTime::acceptedArgCount() const { return _argCount; }
    
}
