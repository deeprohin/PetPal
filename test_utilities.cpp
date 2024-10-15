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
