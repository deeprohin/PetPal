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

// Test performance of health update
TEST(PerformanceTest, UpdateHealthPerformance) {
    PetStats stats;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000000; ++i) {
        stats.updateHealth(1);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    EXPECT_LT(duration.count(), 1.0); // Ensure it runs under 1 second
}

// Test performance of sleep update
TEST(PerformanceTest, UpdateSleepPerformance) {
    PetStats stats;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000000; ++i) {
        stats.updateSleep(-1);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    EXPECT_LT(duration.count(), 1.0); // Ensure it runs under 1 second
}

// Test performance of happiness update
TEST(PerformanceTest, UpdateHappinessPerformance) {
    PetStats stats;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000000; ++i) {
        stats.updateHappiness(1);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    EXPECT_LT(duration.count(), 1.0); // Ensure it runs under 1 second
}

// Test performance of energy update
TEST(PerformanceTest, UpdateEnergyPerformance) {
    PetStats stats;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000000; ++i) {
        stats.updateEnergy(-1);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    EXPECT_LT(duration.count(), 1.0); // Ensure it runs under 1 second
}

// Test combined updates for performance
TEST(PerformanceTest, CombinedStatsUpdatePerformance) {
    PetStats stats;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000000; ++i) {
        stats.updateHunger(-1);
        stats.updateHealth(1);
        stats.updateSleep(-1);
        stats.updateHappiness(1);
        stats.updateEnergy(-1);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    EXPECT_LT(duration.count(), 2.0); // Allow slightly more time for combined updates
}
