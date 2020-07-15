#include <gtest/gtest.h>
#include <random>
#include "../../include/warpedrecord.h"

using namespace timeline;
using namespace locusmap;

class TimelineTest : public ::testing::Test {
protected:
    TimelineTest() :
        t1(std::make_unique<MarkerMap>()),
        t2(std::make_unique<MarkerMap>()),
        t3(std::make_unique<MarkerMap>())
    {}

    void    SetUp() override {
        // example in sample
        t1.insertWarpMarker(0, 0);
        t1.insertWarpMarker(1, 5);
        t1.setEndTempo(10.0);

        // single marker and end_tempo
        t2.insertWarpMarker(90, 1);
        t2.setEndTempo(120);

        // multiple markers overlapping then multiple in a row
        t3.insertWarpMarker(12, 56);
        t3.insertWarpMarker(32, 11);
        t3.insertWarpMarker(33, 10);
        t3.insertWarpMarker(7, 7);
        t3.insertWarpMarker(3, 5);
        t3.insertWarpMarker(5, 6);
        t3.insertWarpMarker(10, 8);
        t3.insertWarpMarker(15, 9);
        t3.insertWarpMarker(19, 25);
        t3.insertWarpMarker(21, 27);
        t3.setEndTempo(40);
    }

    Timeline    t1;
    Timeline    t2;
    Timeline    t3;
};

TEST_F(TimelineTest, insertWarpMarker) {
    t1.insertWarpMarker(2, 100);
    t1.insertWarpMarker(0, 200);
    t1.insertWarpMarker(0, 0);
    t1.insertWarpMarker(1, 5);
    EXPECT_EQ(t1.getBeatFromTime(6), 11);
}

TEST_F(TimelineTest, getTimeFromBeat) {
    EXPECT_EQ(t3.getTimeFromBeat(12.5), 8.5);
    EXPECT_EQ(t3.getTimeFromBeat(17), 17);
    EXPECT_EQ(t3.getTimeFromBeat(0.5), 3.75);
}

TEST_F(TimelineTest, getBeatFromTime) {
    EXPECT_EQ(t1.getBeatFromTime(2), 0.4);
    EXPECT_EQ(t1.getBeatFromTime(6), 11);
    EXPECT_EQ(t2.getBeatFromTime(2), 210);
}

// private member tests

/*TEST_F(TimelineTest, calculateRelationship) {
}

TEST_F(TimelineTest, calculateTimeByTempo) {

}

TEST_F(TimelineTest, calculateBeatByTempo) {
    EXPECT_EQ(t1.calculateBeatByTempo(6.0, {1.0, 5.0}), 11.0);
}*/
