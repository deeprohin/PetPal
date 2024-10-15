// test_state_transitions.cpp

#include <gtest/gtest.h>
#include "PetStats.h"

// Test state transitions for hunger
TEST(PetStatsTest, HungerStateTransition) {
    PetStats stats;
    stats.setHunger(50);
    EXPECT_EQ(stats.getHunger(), 50);

    stats.decreaseHunger(30);
    EXPECT_EQ(stats.getHunger(), 20);

    stats.decreaseHunger(25); // Should not go below 0
    EXPECT_EQ(stats.getHunger(), 0);

    stats.increaseHunger(10);
    EXPECT_EQ(stats.getHunger(), 10);
}

// Test state transitions for health
TEST(PetStatsTest, HealthStateTransition) {
    PetStats stats;
    stats.setHealth(80);
    EXPECT_EQ(stats.getHealth(), 80);

    stats.decreaseHealth(50);
    EXPECT_EQ(stats.getHealth(), 30);

    stats.decreaseHealth(40); // Should not go below 0
    EXPECT_EQ(stats.getHealth(), 0);

    stats.increaseHealth(20);
    EXPECT_EQ(stats.getHealth(), 20);
}

// Test state transitions for sleep
TEST(PetStatsTest, SleepStateTransition) {
    PetStats stats;
    stats.setSleep(40);
    EXPECT_EQ(stats.getSleep(), 40);

    stats.decreaseSleep(30);
    EXPECT_EQ(stats.getSleep(), 10);

    stats.decreaseSleep(15); // Should not go below 0
    EXPECT_EQ(stats.getSleep(), 0);

    stats.increaseSleep(25);
    EXPECT_EQ(stats.getSleep(), 25);
}

// Test state transitions for combined stats
TEST(PetStatsTest, CombinedStateTransition) {
    PetStats stats;
    stats.setHunger(50);
    stats.setHealth(50);
    stats.setSleep(50);

    stats.decreaseHunger(60); // Hunger should not go below 0
    EXPECT_EQ(stats.getHunger(), 0);
    EXPECT_EQ(stats.getHealth(), 50);
    EXPECT_EQ(stats.getSleep(), 50);

    stats.increaseHealth(30);
    EXPECT_EQ(stats.getHealth(), 80); // Health should increase correctly

    stats.decreaseSleep(80); // Sleep should not go below 0
    EXPECT_EQ(stats.getSleep(), 0);
}

// Test extreme state transitions for health
TEST(PetStatsTest, ExtremeHealthTransitions) {
    PetStats stats;
    stats.setHealth(0);
    EXPECT_EQ(stats.getHealth(), 0);

    stats.increaseHealth(50); // Should increase health but not exceed max
    EXPECT_EQ(stats.getHealth(), 50);

    stats.decreaseHealth(100); // Should not go below 0
    EXPECT_EQ(stats.getHealth(), 0);
}

// Test extreme state transitions for hunger
TEST(PetStatsTest, ExtremeHungerTransitions) {
    PetStats stats;
    stats.setHunger(0);
    EXPECT_EQ(stats.getHunger(), 0);

    stats.increaseHunger(150); // Should cap at max hunger
    EXPECT_EQ(stats.getHunger(), 100); // Assuming 100 is max hunger

    stats.decreaseHunger(200); // Should not go below 0
    EXPECT_EQ(stats.getHunger(), 0);
}

// Test extreme state transitions for sleep
TEST(PetStatsTest, ExtremeSleepTransitions) {
    PetStats stats;
    stats.setSleep(0);
    EXPECT_EQ(stats.getSleep(), 0);

    stats.increaseSleep(200); // Should cap at max sleep
    EXPECT_EQ(stats.getSleep(), 100); // Assuming 100 is max sleep

    stats.decreaseSleep(150); // Should not go below 0
    EXPECT_EQ(stats.getSleep(), 0);
}
