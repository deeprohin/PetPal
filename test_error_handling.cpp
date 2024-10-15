// test_error_handling.cpp

#include <gtest/gtest.h>
#include "SpriteLoader.h"

// Test handling missing image file
TEST(ErrorHandlingTest, MissingImageFile) {
    EXPECT_FALSE(SpriteLoader::loadSprite("NonExistentImage.png"));
}

// Test handling missing font file
TEST(ErrorHandlingTest, MissingFontFile) {
    sf::Font font;
    EXPECT_FALSE(font.loadFromFile("NonExistentFont.ttf"));
}
