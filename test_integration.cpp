// test_integration.cpp

#include <gtest/gtest.h>
#include "AdultAvo.h"
#include "PetStats.h"

TEST(IntegrationTest, EatUpdatesStats) {
    sf::Font font;
    ASSERT_TRUE(font.loadFromFile("Regular.ttf"));
    PetStats stats;
    std::vector<Item> basket;
    int trolleyCount = 0;

    AdultAvo adultAvo;
    adultAvo.eat(/* RenderWindow mock or dummy */, font, basket);
    
    // Assuming eating increases happiness and decreases hunger
    EXPECT_GT(stats.getHappiness(), 50); // Example condition
    EXPECT_LT(stats.getHunger(), 100);    // Example condition
}

// Test sleeping updates stats (sleep and health)
TEST(IntegrationTest, SleepUpdatesStats) {
    sf::Font font;
    ASSERT_TRUE(font.loadFromFile("Regular.ttf"));
    PetStats stats;
    std::vector<Item> basket;
    int trolleyCount = 0;

    AdultAvo adultAvo;
    adultAvo.sleep(/* RenderWindow mock or dummy */, font);

    // Assuming sleeping fully restores sleep and increases health
    EXPECT_EQ(stats.getSleep(), 100);      // Sleep should be fully restored
    EXPECT_GT(stats.getHealth(), 50);      // Health should increase after sleeping
}

// Test playing updates stats (happiness and energy)
TEST(IntegrationTest, PlayUpdatesStats) {
    sf::Font font;
    ASSERT_TRUE(font.loadFromFile("Regular.ttf"));
    PetStats stats;
    std::vector<Item> basket;
    int trolleyCount = 0;

    AdultAvo adultAvo;
    adultAvo.play(/* RenderWindow mock or dummy */, font);

    // Assuming playing increases happiness and decreases energy
    EXPECT_GT(stats.getHappiness(), 50);   // Happiness should increase
    EXPECT_LT(stats.getEnergy(), 100);     // Energy should decrease
}

// Test taking a shower updates stats (health and cleanliness)
TEST(IntegrationTest, ShowerUpdatesStats) {
    sf::Font font;
    ASSERT_TRUE(font.loadFromFile("Regular.ttf"));
    PetStats stats;
    std::vector<Item> basket;
    int trolleyCount = 0;

    AdultAvo adultAvo;
    adultAvo.shower(/* RenderWindow mock or dummy */, font);

    // Assuming showering restores cleanliness and improves health
    EXPECT_EQ(stats.getCleanliness(), 100);  // Cleanliness should be fully restored
    EXPECT_GT(stats.getHealth(), 50);        // Health should increase after showering
}

// Test feeding decreases hunger and increases happiness
TEST(IntegrationTest, FeedUpdatesStats) {
    sf::Font font;
    ASSERT_TRUE(font.loadFromFile("Regular.ttf"));
    PetStats stats;
    std::vector<Item> basket;
    basket.push_back(Item{"Apple", 50, 1});  // Add an item to feed
    int trolleyCount = 0;

    AdultAvo adultAvo;
    adultAvo.feed(/* RenderWindow mock or dummy */, font, basket);

    // Assuming feeding decreases hunger and increases happiness
    EXPECT_LT(stats.getHunger(), 100);       // Hunger should decrease after feeding
    EXPECT_GT(stats.getHappiness(), 50);     // Happiness should increase after feeding
}

// Test taking medicine updates health
TEST(IntegrationTest, MedicineUpdatesHealth) {
    sf::Font font;
    ASSERT_TRUE(font.loadFromFile("Regular.ttf"));
    PetStats stats;
    std::vector<Item> basket;
    int trolleyCount = 0;

    AdultAvo adultAvo;
    adultAvo.takeMedicine(/* RenderWindow mock or dummy */, font);

    // Assuming taking medicine restores health
    EXPECT_EQ(stats.getHealth(), 100);       // Health should be fully restored
}

// Test shopping decreases money and adds items to basket
TEST(IntegrationTest, ShoppingUpdatesBasketAndMoney) {
    sf::Font font;
    ASSERT_TRUE(font.loadFromFile("Regular.ttf"));
    PetStats stats;
    std::vector<Item> basket;
    stats.changeMoney(1000);  // Start with some money

    AdultAvo adultAvo;
    adultAvo.shop(/* RenderWindow mock or dummy */, font, basket, stats);

    // Assuming shopping adds items to basket and decreases money
    EXPECT_LT(stats.getMoney(), 1000);      // Money should decrease after shopping
    EXPECT_GT(basket.size(), 0);            // Basket should have new items
}

// Test completing a mini-game increases money
TEST(IntegrationTest, MiniGameUpdatesMoney) {
    sf::Font font;
    ASSERT_TRUE(font.loadFromFile("Regular.ttf"));
    PetStats stats;
    mini_game game;

    AdultAvo adultAvo;
    game.update();  // Simulate mini-game play
    stats.changeMoney(game.money_earned_end());

    // Verify money earned after completing the mini-game
    EXPECT_GT(stats.getMoney(), 0);  // Money should increase after mini-game
}
