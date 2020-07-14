#include "../../include/Command.h"
#include <iostream>

namespace command {

InsertWarpMarker::InsertWarpMarker(Timeline& timeline) :
    _timeline(timeline),
    _beat(0.0),
    _timestamp(0.0)
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

DefineEndTempo::DefineEndTempo(Timeline& timeline) :
    _timeline(timeline),
    _tempo(0.0)
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

ConvertTimeToBeat::ConvertTimeToBeat(Timeline& timeline) :
    _timeline(timeline),
    _time(0.0)
{}

int ConvertTimeToBeat::invoke()
{
    if (auto ret = _timeline.getBeatFromTime(_time); ret != -1) {
        std::cout << ret << std::endl;
        return 0;
    }
    return 1;
}

void    ConvertTimeToBeat::assignInput(const commandList& args)
{
    _time = std::stof(args[0]);
}

ConvertBeatToTime::ConvertBeatToTime(Timeline& timeline) :
    _timeline(timeline),
    _beat(0.0)
{}

int ConvertBeatToTime::invoke()
{
    if (auto time = _timeline.getTimeFromBeat(_beat); time != -1) {
        std::cout << time << std::endl;
        return 0;
    }
    return 1;
}

void    ConvertBeatToTime::assignInput(const commandList& args)
{
    _beat = std::stof(args[0]);
}

}
