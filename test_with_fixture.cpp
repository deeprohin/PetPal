// test_with_fixture.cpp
#include <gtest/gtest.h>
#include "PetStats.h"

class PetStatsFixture : public ::testing::Test {
protected:
    PetStats stats;

    void SetUp() override {
        stats.setHunger(50);
        stats.setHealth(50);
        stats.setSleep(50);
    }

    void TearDown() override {
        // Clean-up code if needed
    }
};

TEST_F(PetStatsFixture, IncreaseHunger) {
    stats.increaseHunger(20);
    EXPECT_EQ(stats.getHunger(), 70);
}

TEST_F(PetStatsFixture, DecreaseHealth) {
    stats.decreaseHealth(30);
    EXPECT_EQ(stats.getHealth(), 20);
}

TEST_F(PetStatsFixture, MaxSleep) {
    stats.maxSleep();
    EXPECT_EQ(stats.getSleep(), 100);
}

// Test decreasing hunger below zero
TEST_F(PetStatsFixture, DecreaseHungerBelowZero) {
    stats.decreaseHunger(60); // Decrease hunger by more than current value
    EXPECT_EQ(stats.getHunger(), 0); // Should not go below zero
}

// Test increasing health above maximum
TEST_F(PetStatsFixture, IncreaseHealthAboveMax) {
    stats.setHealth(90);
    stats.increaseHealth(20); // Attempt to increase health beyond max
    EXPECT_EQ(stats.getHealth(), 100); // Should cap at 100
}

// Test sleep state transition
TEST_F(PetStatsFixture, SleepStateTransition) {
    stats.setSleep(30);
    stats.increaseSleep(50);
    EXPECT_EQ(stats.getSleep(), 80); // Should increase sleep
    stats.decreaseSleep(100); // Should not go below zero
    EXPECT_EQ(stats.getSleep(), 0);
}

// Test resetting all stats
TEST_F(PetStatsFixture, ResetStats) {
    stats.maxHunger();
    stats.maxHealth();
    stats.maxSleep();
    
    // Assuming you have a resetStats() method
    stats.resetStats(); // Hypothetical method to reset all stats
    EXPECT_EQ(stats.getHunger(), 100);
    EXPECT_EQ(stats.getHealth(), 100);
    EXPECT_EQ(stats.getSleep(), 100);
}
