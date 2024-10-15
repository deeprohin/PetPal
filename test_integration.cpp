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
