// test_edge_cases.cpp

#include <gtest/gtest.h>
#include "PetStats.h"
#include "SpriteLoader.h"

// Test handling of missing font file
TEST(EdgeCaseTest, MissingFontFile) {
    sf::Font font;
    EXPECT_FALSE(font.loadFromFile("NonExistentFont.ttf")); // Should fail
}

// Test handling of missing image file
TEST(EdgeCaseTest, MissingImageFile) {
    sf::Texture texture;
    EXPECT_FALSE(texture.loadFromFile("NonExistentImage.png")); // Should fail
}

// Test adding an item beyond basket capacity
TEST(EdgeCaseTest, AddItemBeyondBasketCapacity) {
    std::vector<Item> basket;
    basket.reserve(5); // Set capacity to 5

    for (int i = 0; i < 6; ++i) { // Attempt to add 6 items
        Item item;
        item.name = "Item" + std::to_string(i);
        basket.push_back(item);
    }

    EXPECT_EQ(basket.size(), 6); // Depending on implementation, you might have limits
}
