#include <gtest/gtest.h>
#include <random>
#include <chrono>
#include "../../include/warpedrecord.h"

using namespace locusmap;
using namespace std::chrono;

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

TEST_F(MarkerMapTest, upperBoundAboveMap) {
    EXPECT_FALSE(m2.upperBoundAboveMap(8));
    m2.insertRelationship(5, 7);
    EXPECT_TRUE(m2.upperBoundAboveMap(4));
    EXPECT_DOUBLE_EQ(m2.upperBoundAboveMap(4)->above, 5);
    EXPECT_FALSE(m2.upperBoundAboveMap(7));
}

TEST_F(MarkerMapTest, lowerBoundAboveMap) {
    EXPECT_FALSE(m2.lowerBoundAboveMap(8));
    m2.insertRelationship(5, 7);
    EXPECT_TRUE(m2.lowerBoundAboveMap(6));
    EXPECT_DOUBLE_EQ(m2.lowerBoundAboveMap(6)->above, 5);
    EXPECT_FALSE(m2.lowerBoundAboveMap(1));
}

TEST_F(MarkerMapTest, upperBoundBelowMap) {
    EXPECT_FALSE(m2.upperBoundBelowMap(8));
    m2.insertRelationship(7, 5);
    EXPECT_TRUE(m2.upperBoundBelowMap(4));
    EXPECT_DOUBLE_EQ(m2.upperBoundBelowMap(4)->below, 5);
    EXPECT_FALSE(m2.upperBoundBelowMap(7));
}

TEST_F(MarkerMapTest, lowerBoundBelowMap) {
    EXPECT_FALSE(m2.upperBoundBelowMap(8));
    m2.insertRelationship(7, 5);
    EXPECT_TRUE(m2.upperBoundBelowMap(4));
    EXPECT_DOUBLE_EQ(m2.upperBoundBelowMap(4)->below, 5);
    EXPECT_FALSE(m2.upperBoundBelowMap(7));
}

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
    // stress test

    auto start = high_resolution_clock::now();
    for (int i = 0; i < 10000000; i += 2)
        m1.insertRelationship(distr(gen), distr(gen));
    auto stop = high_resolution_clock::now();
    std::chrono::duration<double> elapsed = stop - start;
    EXPECT_LE(elapsed.count(), 2);
}
