#include <gtest/gtest.h>

int test() {
    return false;
}

TEST(testsuite, test) {
    ASSERT_EQ(test(), true);
}
