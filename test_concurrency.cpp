// test_concurrency.cpp

#include <gtest/gtest.h>
#include <thread>
#include "PetStats.h"

TEST(ConcurrencyTest, ConcurrentStatUpdates) {
    PetStats stats;
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
    EXPECT_EQ(stats.getHunger(), 100 - 1000); // Example condition
    EXPECT_EQ(stats.getHealth(), 0 + 1000);  // Example condition
}
