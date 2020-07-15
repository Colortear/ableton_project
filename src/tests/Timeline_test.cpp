#include <gtest/gtest.h>
#include <Timeline_test.h>
#include "../../include/warpedrecord.h"

using namespace timeline;
using namespace locusmap;

TEST_F(TimelineTest, insertWarpMarker) {
}

TEST_F(TimelineTest, getTimeFromBeat) {
}

TEST_F(TimelineTest, getBeatFromTime) {
    EXPECT_EQ(t1.getTimeFromBeat(0.5), 2.5);
    EXPECT_EQ(t1.getBeatFromTime(6.0), 11.0);
}

TEST_F(TimelineTest, calculateRelationship) {
}

TEST_F(TimelineTest, calculateTimeByTempo) {

}

TEST_F(TimelineTest, calculateBeatByTempo) {
    EXPECT_EQ(t1.calculateBeatByTempo(6.0, {1.0, 5.0}), 11.0);
}
