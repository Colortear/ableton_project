#include "../include/warpedrecord.h"
#include <utility>

namespace command {

void    registerCommands(CommandProcessor& cp, Timeline& timeline)
{
    cp.registerCommand<InsertWarpMarker, Timeline&>("marker", timeline);
    cp.registerCommand<DefineEndTempo, Timeline&>("end_tempo", timeline);
    cp.registerCommand<ConvertTimeToBeat, Timeline&>("s2b", timeline);
    cp.registerCommand<ConvertBeatToTime, Timeline&>("b2s", timeline);
}

}
