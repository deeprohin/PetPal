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
