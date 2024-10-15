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

// Test hunger decreases after activity (playing a mini-game)
TEST(PetStatsTest, HungerDecreasesAfterActivity) {
    PetStats stats;
    stats.maxHunger();  // Set hunger to max (100)

    // Simulate playing a mini-game which decreases hunger
    stats.updateHunger(-20);  // Assuming playing decreases hunger by 20

    EXPECT_EQ(stats.getHunger(), 80);  // Hunger should now be 80
}
