#include <gtest/gtest.h>
#include <random>
#include "../../include/warpedrecord.h"

using namespace locusmap;

class MarkerMapTest : public ::testing::Test {
protected:
    MarkerMapTest() :
    m1(MarkerMap()),
    m2(MarkerMap()) {}

    void    SetUp() override {
        m1.insertRelationship(0.0, 0.0);
        m1.insertRelationship(1.0, 5.0);
    }

    MarkerMap   m1;
    MarkerMap   m2;
};

TEST_F(MarkerMapTest, insertRelationship) {
    std::random_device  rd;
    std::mt19937        gen(rd());
    std::uniform_int_distribution<> distr(0, 100);

    for (int i = 0; i < 200; i += 2)
        m1.insertRelationship(distr(gen), distr(gen));
    m1.insertRelationship(0, 200);
    m1.insertRelationship(200, 0);
    EXPECT_DOUBLE_EQ(m1.aSize(), 1lu);
    EXPECT_DOUBLE_EQ(m1.bSize(), 1lu);
}

// private member tests

/*TEST_F(MarkerMapTest, isIntersecting) {
    MarkerMap   local;
    // parallel
    EXPECT_FALSE(local.isIntersecting({8.0, 7.0}, {9.0, 10.0}));
    // equidistant
    EXPECT_TRUE(local.isIntersecting({1.0, 7.0}, {7.0, 1.0}));
    // touching points
    EXPECT_TRUE(local.isIntersecting({5.0, 6.0}, {8.0, 6.0}));
    // touching points reverse
    EXPECT_TRUE(local.isIntersecting({6.0, 5.0}, {6.0, 8.0}));
    // slope same direction
    EXPECT_TRUE(local.isIntersecting({1.0, 8.0}, {0.0, 9.0}));
    EXPECT_TRUE(local.isIntersecting({0, 200}, {200, 0}));
}*/
