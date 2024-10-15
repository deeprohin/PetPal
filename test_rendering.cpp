// test_rendering.cpp

#include <gtest/gtest.h>
#include "quotesFile.h"
#include "pet_stats.h"

// Test getting a random quote
TEST(QuoteTest, GetRandomQuote) {
    std::string petType = "adult_avo";
    std::string quote = getRandomQuote(petType);
    EXPECT_FALSE(quote.empty());  // Check that quote is not empty
}

// Test rendering stats (Hunger, Health, Sleep)
TEST(RenderingTest, RenderStats) {
    sf::Font font;
    ASSERT_TRUE(font.loadFromFile("Regular.ttf")); // Ensure font loads successfully
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");

    PetStats petStats;
    petStats.maxHunger();
    petStats.renderStats(window, font);

    // No direct way to test rendered output, but ensure function executes without error
    SUCCEED();  // If no crash or error, assume success
}

// Test getting a specific quote for baby_avo
TEST(QuoteTest, GetSpecificQuoteForBabyAvo) {
    std::string petType = "baby_avo";
    std::string quote = getRandomQuote(petType);
    EXPECT_FALSE(quote.empty());  // Ensure the quote is not empty
}

// Test rendering hunger stats
TEST(RenderingTest, RenderHungerStats) {
    sf::Font font;
    ASSERT_TRUE(font.loadFromFile("Regular.ttf"));
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");

    PetStats petStats;
    petStats.setHunger(50); // Set hunger for rendering
    petStats.renderStats(window, font);

    // No direct way to test rendered output, but ensure function executes without error
    SUCCEED();  // If no crash or error, assume success
}

// Test rendering health stats
TEST(RenderingTest, RenderHealthStats) {
    sf::Font font;
    ASSERT_TRUE(font.loadFromFile("Regular.ttf"));
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");

    PetStats petStats;
    petStats.setHealth(75); // Set health for rendering
    petStats.renderStats(window, font);

    // No direct way to test rendered output, but ensure function executes without error
    SUCCEED();  // If no crash or error, assume success
}

// Test rendering sleep stats
TEST(RenderingTest, RenderSleepStats) {
    sf::Font font;
    ASSERT_TRUE(font.loadFromFile("Regular.ttf"));
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");

    PetStats petStats;
    petStats.setSleep(30); // Set sleep for rendering
    petStats.renderStats(window, font);

    // No direct way to test rendered output, but ensure function executes without error
    SUCCEED();  // If no crash or error, assume success
}

// Test getting a random quote for a non-existent pet type
TEST(QuoteTest, GetRandomQuoteForNonExistentPet) {
    std::string petType = "non_existent_pet";
    std::string quote = getRandomQuote(petType);
    EXPECT_TRUE(quote.empty());  // Expect empty quote since pet type does not exist
}
