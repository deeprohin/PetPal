// test_state_transitions.cpp
#include <gtest/gtest.h>
#include "PetStats.h"

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
