// test_concurrency.cpp

#include <gtest/gtest.h>
#include <thread>
#include "PetStats.h"

// Test concurrent updates of hunger and health
TEST(ConcurrencyTest, ConcurrentStatUpdates) {
    PetStats stats;
    stats.maxHunger();
    stats.maxHealth();
    
    auto updateHunger = [&stats]() {
        for (int i = 0; i < 1000; ++i) {
            stats.updateHunger(-1);
        }
    };

    auto updateHealth = [&stats]() {
        for (int i = 0; i < 1000; ++i) {
            stats.updateHealth(1);
        }
    };

    std::thread thread1(updateHunger);
    std::thread thread2(updateHealth);

    thread1.join();
    thread2.join();

    // Verify that stats are updated correctly
    EXPECT_EQ(stats.getHunger(), 100 - 1000);  // Hunger decreases by 1000
    EXPECT_EQ(stats.getHealth(), 100 + 1000);  // Health increases by 1000
}

// Test concurrent updates of hunger and sleep
TEST(ConcurrencyTest, ConcurrentHungerAndSleep) {
    PetStats stats;
    stats.maxHunger();
    stats.maxSleep();
    
    auto updateHunger = [&stats]() {
        for (int i = 0; i < 500; ++i) {
            stats.updateHunger(-2);  // Decrease hunger faster
        }
    };

    auto updateSleep = [&stats]() {
        for (int i = 0; i < 500; ++i) {
            stats.updateSleep(-1);  // Sleep decreases normally
        }
    };

    std::thread thread1(updateHunger);
    std::thread thread2(updateSleep);

    thread1.join();
    thread2.join();

    EXPECT_EQ(stats.getHunger(), 100 - 500 * 2);  // Hunger decreases by 1000
    EXPECT_EQ(stats.getSleep(), 100 - 500);       // Sleep decreases by 500
}

// Test concurrent increase of all stats (hunger, health, sleep)
TEST(ConcurrencyTest, ConcurrentIncreaseAllStats) {
    PetStats stats;
    stats.maxHunger();
    stats.maxHealth();
    stats.maxSleep();
    
    auto increaseHunger = [&stats]() {
        for (int i = 0; i < 1000; ++i) {
            stats.updateHunger(1);
        }
    };

    auto increaseHealth = [&stats]() {
        for (int i = 0; i < 1000; ++i) {
            stats.updateHealth(1);
        }
    };

    auto increaseSleep = [&stats]() {
        for (int i = 0; i < 1000; ++i) {
            stats.updateSleep(1);
        }
    };

    std::thread thread1(increaseHunger);
    std::thread thread2(increaseHealth);
    std::thread thread3(increaseSleep);

    thread1.join();
    thread2.join();
    thread3.join();

    // All stats should max out at 100
    EXPECT_EQ(stats.getHunger(), 100);
    EXPECT_EQ(stats.getHealth(), 100);
    EXPECT_EQ(stats.getSleep(), 100);
}

// Test multiple threads reducing hunger simultaneously
TEST(ConcurrencyTest, MultipleThreadsReduceHunger) {
    PetStats stats;
    stats.maxHunger();
    
    auto reduceHunger = [&stats]() {
        for (int i = 0; i < 500; ++i) {
            stats.updateHunger(-1);
        }
    };

    std::thread thread1(reduceHunger);
    std::thread thread2(reduceHunger);
    std::thread thread3(reduceHunger);

    thread1.join();
    thread2.join();
    thread3.join();

    EXPECT_EQ(stats.getHunger(), 100 - 500 * 3);  // Hunger reduced by 1500 total
}

// Test multiple threads increasing health and reducing sleep
TEST(ConcurrencyTest, IncreaseHealthAndReduceSleep) {
    PetStats stats;
    stats.maxHealth();
    stats.maxSleep();
    
    auto increaseHealth = [&stats]() {
        for (int i = 0; i < 1000; ++i) {
            stats.updateHealth(1);
        }
    };

    auto reduceSleep = [&stats]() {
        for (int i = 0; i < 1000; ++i) {
            stats.updateSleep(-1);
        }
    };

    std::thread thread1(increaseHealth);
    std::thread thread2(reduceSleep);

    thread1.join();
    thread2.join();

    EXPECT_EQ(stats.getHealth(), 100 + 1000);  // Health increases
    EXPECT_EQ(stats.getSleep(), 100 - 1000);   // Sleep decreases
}

// Test edge case: concurrent updates that exceed stat limits
TEST(ConcurrencyTest, StatExceedLimits) {
    PetStats stats;
    stats.maxHealth();
    stats.maxHunger();
    stats.maxSleep();

    auto increaseHunger = [&stats]() {
        for (int i = 0; i < 2000; ++i) {
            stats.updateHunger(1);  // Exceed max hunger
        }
    };

    auto decreaseHealth = [&stats]() {
        for (int i = 0; i < 2000; ++i) {
            stats.updateHealth(-1);  // Reduce health
        }
    };

    std::thread thread1(increaseHunger);
    std::thread thread2(decreaseHealth);

    thread1.join();
    thread2.join();

    EXPECT_EQ(stats.getHunger(), 100);   // Hunger should not exceed 100
    EXPECT_EQ(stats.getHealth(), 0);     // Health should drop to 0
}

