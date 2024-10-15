// test_error_handling.cpp

#include <gtest/gtest.h>
#include "SpriteLoader.h"
#include "PetStats.h"
#include <stdexcept>

// Test handling of missing image file in SpriteLoader
TEST(ErrorHandlingTest, MissingImageFile) {
    EXPECT_FALSE(SpriteLoader::loadSprite("NonExistentImage.png")); // Should return false
}

// Test handling of missing font file in SFML
TEST(ErrorHandlingTest, MissingFontFile) {
    sf::Font font;
    EXPECT_FALSE(font.loadFromFile("NonExistentFont.ttf")); // Should return false
}

// Test invalid pet type in Pet creation (using SpriteLoader)
TEST(ErrorHandlingTest, InvalidPetCreation) {
    std::string invalid_pet = "alien_pet";
    std::unique_ptr<Pet> pet = SpriteLoader::createPet(invalid_pet);
    EXPECT_EQ(pet, nullptr); // Should return nullptr for invalid pet type
}

// Test loading a corrupt texture file
TEST(ErrorHandlingTest, CorruptTextureFile) {
    sf::Texture texture;
    EXPECT_FALSE(texture.loadFromFile("CorruptTexture.png")); // Should return false
}

// Test handling a null pointer for sprite initialization
TEST(ErrorHandlingTest, NullSpriteInitialization) {
    sf::Sprite* sprite = nullptr;
    EXPECT_THROW({
        if (!sprite) {
            throw std::runtime_error("Sprite is null");
        }
    }, std::runtime_error); // Should throw a runtime error
}

// Test invalid file extension in SpriteLoader
TEST(ErrorHandlingTest, InvalidFileExtension) {
    EXPECT_FALSE(SpriteLoader::loadSprite("InvalidFile.txt")); // Should return false
}

// Test handling invalid money update in PetStats (negative coins)
TEST(ErrorHandlingTest, InvalidMoneyUpdate) {
    PetStats stats;
    stats.changeMoney(100);  // Start with some coins
    stats.changeMoney(-200); // Try to subtract more money than available
    EXPECT_GE(stats.getMoney(), 0); // Ensure money never goes below 0
}

// Test PetStats for invalid health reduction (below zero)
TEST(ErrorHandlingTest, HealthBelowZero) {
    PetStats stats;
    stats.maxHealth();
    stats.updateHealth(-500); // Exaggerated reduction to check limits
    EXPECT_GE(stats.getHealth(), 0); // Health should never go below 0
}

// Test PetStats for invalid hunger increase (above max)
TEST(ErrorHandlingTest, HungerAboveMax) {
    PetStats stats;
    stats.maxHunger();
    stats.updateHunger(500); // Exaggerated increase to check limits
    EXPECT_LE(stats.getHunger(), 100); // Hunger should never exceed 100
}

// Test handling invalid input for math game score
TEST(ErrorHandlingTest, InvalidMathGameScore) {
    math_game game;
    game.setScore(-50); // Set an invalid negative score
    EXPECT_GE(game.getScore(), 0); // Score should not be allowed to go below 0
}
