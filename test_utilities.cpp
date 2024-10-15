// test_utilities.cpp

#include <gtest/gtest.h>
#include "sprite_loader.h"

// Test loading sprites
TEST(UtilityTest, LoadSprites) {
    EXPECT_TRUE(SpriteLoader::loadResources());  // Ensure sprites are loaded successfully
}

// Test loading font
TEST(UtilityTest, LoadFont) {
    sf::Font font;
    EXPECT_TRUE(font.loadFromFile("Regular.ttf"));  // Ensure font is loaded successfully
}

// Test loading a non-existent sprite
TEST(UtilityTest, LoadNonExistentSprite) {
    EXPECT_FALSE(SpriteLoader::loadSprite("NonExistentSprite.png"));  // Should fail to load
}

// Test loading a non-existent font
TEST(UtilityTest, LoadNonExistentFont) {
    sf::Font font;
    EXPECT_FALSE(font.loadFromFile("NonExistentFont.ttf"));  // Should fail to load
}

// Test loading multiple sprites at once
TEST(UtilityTest, LoadMultipleSprites) {
    EXPECT_TRUE(SpriteLoader::loadResources());  // Assume this function loads multiple sprites
    // Check specific sprites loaded if you have identifiers
    EXPECT_TRUE(SpriteLoader::isSpriteLoaded("Sprite1.png"));
    EXPECT_TRUE(SpriteLoader::isSpriteLoaded("Sprite2.png"));
}

// Test cleanup functionality
TEST(UtilityTest, CleanupResources) {
    SpriteLoader::loadResources();  // Load some resources
    SpriteLoader::cleanup();         // Cleanup resources

    // Verify that resources are no longer available
    EXPECT_FALSE(SpriteLoader::isSpriteLoaded("Sprite1.png"));
    EXPECT_FALSE(SpriteLoader::isSpriteLoaded("Sprite2.png"));
}

// Test checking if a sprite is loaded
TEST(UtilityTest, IsSpriteLoaded) {
    SpriteLoader::loadResources();  // Load resources first
    EXPECT_TRUE(SpriteLoader::isSpriteLoaded("Sprite1.png"));  // Ensure sprite is loaded
    EXPECT_FALSE(SpriteLoader::isSpriteLoaded("NonExistentSprite.png"));  // Should not be loaded
}

// Test load sprite with invalid parameters
TEST(UtilityTest, LoadSpriteWithInvalidParams) {
    EXPECT_FALSE(SpriteLoader::loadSprite(""));  // Empty string should fail
    EXPECT_FALSE(SpriteLoader::loadSprite("Invalid/Path/Sprite.png"));  // Invalid path should fail
}
