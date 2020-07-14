#include "../include/warpedrecord.h"
#include <utility>

using namespace timeline;

namespace command {

void    registerCommands(CommandProcessor& cp, ITimeline& timeline)
{
    cp.registerCommand<InsertWarpMarker, ITimeline&>("marker", timeline);
    cp.registerCommand<DefineEndTempo, ITimeline&>("end_tempo", timeline);
    cp.registerCommand<ConvertTimeToBeat, ITimeline&>("s2b", timeline);
    cp.registerCommand<ConvertBeatToTime, ITimeline&>("b2s", timeline);
}

}
