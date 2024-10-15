// test_parameterized.cpp
#include <gtest/gtest.h>
#include "PetStats.h"

// Define a test fixture for parameterized tests
class PetStatsHungerTest : public ::testing::TestWithParam<std::pair<int, int>> {
};

// Test hunger decrease with various inputs
TEST_P(PetStatsHungerTest, DecreaseHunger) {
    PetStats stats;
    stats.setHunger(100);
    int decreaseAmount = GetParam().first;
    int expected = GetParam().second;

    stats.decreaseHunger(decreaseAmount);
    EXPECT_EQ(stats.getHunger(), expected);
}

// Instantiate the test case with different parameters
INSTANTIATE_TEST_SUITE_P(
    DecreaseHungerTests,
    PetStatsHungerTest,
    ::testing::Values(
        std::make_pair(30, 70),
        std::make_pair(100, 0),
        std::make_pair(150, 0)
    )
);
