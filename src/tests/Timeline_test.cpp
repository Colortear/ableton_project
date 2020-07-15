#include <gtest/gtest.h>
#include <random>
#include "../../include/warpedrecord.h"

using namespace timeline;
using namespace locusmap;

class TimelineTest : public ::testing::Test {
protected:
    TimelineTest() :
        t1(std::make_unique<MarkerMap>()),
        t2(std::make_unique<MarkerMap>())
    {}

    void    SetUp() override {
        // example in sample
        t1.insertWarpMarker(0.0, 0.0);
        t1.insertWarpMarker(1.0, 5.0);
        t1.setEndTempo(10.0);

        // single marker and end_tempo
        t2.insertWarpMarker(90, 1);
        t2.setEndTempo(120);
    }

    Timeline    t1;
    Timeline    t2;
};

TEST_F(TimelineTest, insertWarpMarker) {
    t1.insertWarpMarker(2, 100);
    t1.insertWarpMarker(0, 200);
    t1.insertWarpMarker(0, 0);
    t1.insertWarpMarker(1, 5);
    EXPECT_EQ(t1.getBeatFromTime(6.0), 11.0);
}

TEST_F(TimelineTest, getTimeFromBeat) {
}

TEST_F(TimelineTest, getBeatFromTime) {
    EXPECT_EQ(t1.getBeatFromTime(2.5), 0.5);
    EXPECT_EQ(t1.getBeatFromTime(6.0), 11.0);
    EXPECT_EQ(t2.getBeatFromTime(2.0), 210);
}

// private member tests

/*TEST_F(TimelineTest, calculateRelationship) {
}

TEST_F(TimelineTest, calculateTimeByTempo) {

}

TEST_F(TimelineTest, calculateBeatByTempo) {
    EXPECT_EQ(t1.calculateBeatByTempo(6.0, {1.0, 5.0}), 11.0);
}*/
