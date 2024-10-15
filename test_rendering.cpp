// test_rendering.cpp

#include <gtest/gtest.h>
#include "quotesFile.h"
#include "pet_stats.h"

// Test getting random quote
TEST(QuoteTest, GetRandomQuote) {
    std::string petType = "adult_avo";
    std::string quote = getRandomQuote(petType);
    EXPECT_FALSE(quote.empty());  // Check that quote is not empty
}

// Test rendering stats (Hunger, Health, Sleep)
TEST(RenderingTest, RenderStats) {
    sf::Font font;
    font.loadFromFile("Regular.ttf");
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");

    PetStats petStats;
    petStats.maxHunger();
    petStats.renderStats(window, font);

    // No direct way to test rendered output, but ensure function executes without error
    SUCCEED();  // If no crash or error, assume success
}
