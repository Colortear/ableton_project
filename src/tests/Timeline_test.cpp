#include "../../include/test/gtest/gtest.h"
#include "../../include/warpedrecord.h"

using namespace timeline;
using namespace locusmap;

class TimelineTest : public ::testing::Test {
protected:
    TimelineTest() :
        t1(Timeline{std::make_unique<MarkerMap>()})
    {}

    void    SetUp() override {
        t1.insertWarpMarker(0.0, 0.0);
        t1.insertWarpMarker(1.0, 5.0);
        t1.setEndTempo(10.0);
    }

    Timeline    t1;
};

TEST_F(TimelineTest, getBeatFromTime) {
    EXPECT_EQ(t1.getTimeFromBeat(0.5), 2.5);
    EXPECT_EQ(t1.getBeatFromTime(6.0), 11.0);
}
