// test_game_mechanics.cpp

#include <gtest/gtest.h>
#include "pet_stats.h"
#include "mini_game.h"

// Test updating pet stats (hunger, health, sleep)
TEST(PetStatsTest, HungerMax) {
    PetStats stats;
    stats.maxHunger();
    EXPECT_EQ(stats.getHunger(), 100);
}

TEST(PetStatsTest, HealthMax) {
    PetStats stats;
    stats.maxHealth();
    EXPECT_EQ(stats.getHealth(), 100);
}

TEST(PetStatsTest, SleepMax) {
    PetStats stats;
    stats.maxSleep();
    EXPECT_EQ(stats.getSleep(), 100);
}

// Test mini-game money earning functionality
TEST(MiniGameTest, EarnMoney) {
    mini_game game;
    game.update();
    EXPECT_GT(game.money_earned_end(), 0);  // Ensure the mini-game gives money at the end
}
