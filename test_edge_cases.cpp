// test_edge_cases.cpp

#include <gtest/gtest.h>
#include "PetStats.h"
#include "SpriteLoader.h"
#include <stdexcept>

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

// Test PetStats handling negative hunger values
TEST(EdgeCaseTest, NegativeHungerValue) {
    PetStats stats;
    stats.maxHunger();
    
    stats.updateHunger(-200);  // Try to reduce hunger below 0
    EXPECT_GE(stats.getHunger(), 0); // Hunger should never go below 0
}

// Test PetStats handling negative health values
TEST(EdgeCaseTest, NegativeHealthValue) {
    PetStats stats;
    stats.maxHealth();

    stats.updateHealth(-200); // Try to reduce health below 0
    EXPECT_GE(stats.getHealth(), 0);  // Health should never go below 0
}

// Test invalid user input for creating a pet
TEST(EdgeCaseTest, InvalidPetCreation) {
    std::string invalid_pet = "unknown_pet";
    std::unique_ptr<Pet> pet = SpriteLoader::createPet(invalid_pet);
    EXPECT_EQ(pet, nullptr); // Should return nullptr for invalid pet
}

// Test PetStats handling maximum hunger limit
TEST(EdgeCaseTest, MaxHungerLimit) {
    PetStats stats;
    stats.maxHunger();
    
    stats.updateHunger(200);  // Try to exceed maximum hunger
    EXPECT_LE(stats.getHunger(), 100); // Hunger should never exceed 100
}

// Test PetStats handling maximum health limit
TEST(EdgeCaseTest, MaxHealthLimit) {
    PetStats stats;
    stats.maxHealth();

    stats.updateHealth(200); // Try to exceed maximum health
    EXPECT_LE(stats.getHealth(), 100);  // Health should never exceed 100
}

// Test PetStats when stats are updated very rapidly
TEST(EdgeCaseTest, RapidStatUpdates) {
    PetStats stats;
    stats.maxHunger();
    stats.maxHealth();

    for (int i = 0; i < 10000; ++i) {
        stats.updateHunger(-1);
        stats.updateHealth(1);
    }

    EXPECT_GE(stats.getHunger(), 0); // Hunger should not go below 0
    EXPECT_LE(stats.getHealth(), 100); // Health should not exceed 100
}

// Test handling of invalid sprite initialization
TEST(EdgeCaseTest, InvalidSpriteInitialization) {
    EXPECT_THROW({
        sf::Texture texture;
        if (!texture.loadFromFile("NonExistentSprite.png")) {
            throw std::runtime_error("Failed to load sprite");
        }
    }, std::runtime_error);
}
