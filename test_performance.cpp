// test_performance.cpp

#include <gtest/gtest.h>
#include <chrono>
#include "PetStats.h"

TEST(PerformanceTest, UpdateStatsPerformance) {
    PetStats stats;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000000; ++i) {
        stats.updateHunger(-1);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    EXPECT_LT(duration.count(), 1.0); // Ensure it runs under 1 second
}
