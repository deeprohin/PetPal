// test_parameterized.cpp
#include <gtest/gtest.h>
#include "PetStats.h"

// Define a test fixture for parameterized tests on hunger
class PetStatsHungerTest : public ::testing::TestWithParam<std::pair<int, int>> {
};

// Test hunger decrease with various inputs
TEST_P(PetStatsHungerTest, DecreaseHunger) {
    PetStats stats;
    stats.setHunger(100);  // Initial hunger set to 100
    int decreaseAmount = GetParam().first;
    int expected = GetParam().second;

    stats.decreaseHunger(decreaseAmount);
    EXPECT_EQ(stats.getHunger(), expected);
}

// Instantiate the test case with different parameters for hunger decrease
INSTANTIATE_TEST_SUITE_P(
    DecreaseHungerTests,
    PetStatsHungerTest,
    ::testing::Values(
        std::make_pair(30, 70),
        std::make_pair(100, 0),
        std::make_pair(150, 0)  // Hunger should not go below 0
    )
);

// Define a test fixture for parameterized tests on health
class PetStatsHealthTest : public ::testing::TestWithParam<std::pair<int, int>> {
};

// Test health increase with various inputs
TEST_P(PetStatsHealthTest, IncreaseHealth) {
    PetStats stats;
    stats.setHealth(50);  // Initial health set to 50
    int increaseAmount = GetParam().first;
    int expected = GetParam().second;

    stats.increaseHealth(increaseAmount);
    EXPECT_EQ(stats.getHealth(), expected);
}

// Instantiate the test case with different parameters for health increase
INSTANTIATE_TEST_SUITE_P(
    IncreaseHealthTests,
    PetStatsHealthTest,
    ::testing::Values(
        std::make_pair(20, 70),
        std::make_pair(50, 100),
        std::make_pair(70, 100)  // Health should not exceed 100
    )
);

// Define a test fixture for parameterized tests on sleep
class PetStatsSleepTest : public ::testing::TestWithParam<std::pair<int, int>> {
};

// Test sleep decrease with various inputs
TEST_P(PetStatsSleepTest, DecreaseSleep) {
    PetStats stats;
    stats.setSleep(80);  // Initial sleep set to 80
    int decreaseAmount = GetParam().first;
    int expected = GetParam().second;

    stats.decreaseSleep(decreaseAmount);
    EXPECT_EQ(stats.getSleep(), expected);
}

// Instantiate the test case with different parameters for sleep decrease
INSTANTIATE_TEST_SUITE_P(
    DecreaseSleepTests,
    PetStatsSleepTest,
    ::testing::Values(
        std::make_pair(20, 60),
        std::make_pair(50, 30),
        std::make_pair(100, 0)  // Sleep should not go below 0
    )
);

// Define a test fixture for parameterized tests on happiness
class PetStatsHappinessTest : public ::testing::TestWithParam<std::pair<int, int>> {
};

// Test happiness increase with various inputs
TEST_P(PetStatsHappinessTest, IncreaseHappiness) {
    PetStats stats;
    stats.setHappiness(40);  // Initial happiness set to 40
    int increaseAmount = GetParam().first;
    int expected = GetParam().second;

    stats.increaseHappiness(increaseAmount);
    EXPECT_EQ(stats.getHappiness(), expected);
}

// Instantiate the test case with different parameters for happiness increase
INSTANTIATE_TEST_SUITE_P(
    IncreaseHappinessTests,
    PetStatsHappinessTest,
    ::testing::Values(
        std::make_pair(20, 60),
        std::make_pair(50, 90),
        std::make_pair(70, 100)  // Happiness should not exceed 100
    )
);

// Define a test fixture for parameterized tests on energy
class PetStatsEnergyTest : public ::testing::TestWithParam<std::pair<int, int>> {
};

// Test energy decrease with various inputs
TEST_P(PetStatsEnergyTest, DecreaseEnergy) {
    PetStats stats;
    stats.setEnergy(100);  // Initial energy set to 100
    int decreaseAmount = GetParam().first;
    int expected = GetParam().second;

    stats.decreaseEnergy(decreaseAmount);
    EXPECT_EQ(stats.getEnergy(), expected);
}

// Instantiate the test case with different parameters for energy decrease
INSTANTIATE_TEST_SUITE_P(
    DecreaseEnergyTests,
    PetStatsEnergyTest,
    ::testing::Values(
        std::make_pair(30, 70),
        std::make_pair(60, 40),
        std::make_pair(120, 0)  // Energy should not go below 0
    )
);
