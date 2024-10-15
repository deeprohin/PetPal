// test_resource_management.cpp

#include <gtest/gtest.h>
#include "EatingAdultAvo.h"

// Test that the destructor cleans up the window properly
TEST(ResourceManagementTest, DestructorCleansUpWindow) {
    // Use smart pointers to track destruction
    std::unique_ptr<EatingAdultAvo> eatingWindow;
    {
        sf::Font font;
        ASSERT_TRUE(font.loadFromFile("Regular.ttf"));
        int trolleyCount = 0;
        eatingWindow = std::make_unique<EatingAdultAvo>(font, trolleyCount);
        // Window is allocated inside EatingAdultAvo
    }
    // When eatingWindow goes out of scope, the destructor should clean up
    eatingWindow.reset();
    // If using tools like Valgrind, you can verify no memory leaks occur
    SUCCEED(); // If no crash or leaks, assume success
}

// Test resource loading and cleanup
TEST(ResourceManagementTest, ResourceLoadingAndCleanup) {
    {
        sf::Font font;
        ASSERT_TRUE(font.loadFromFile("Regular.ttf"));
        int trolleyCount = 0;
        EatingAdultAvo eatingWindow(font, trolleyCount);
        // Perform operations
    }
    // After the block, all resources should be cleaned up
    SUCCEED(); // Use external tools to verify
}

// Test loading an invalid font
TEST(ResourceManagementTest, LoadInvalidFont) {
    sf::Font font;
    EXPECT_FALSE(font.loadFromFile("NonExistentFont.ttf")); // Should fail
}

// Test that multiple instances of EatingAdultAvo do not leak resources
TEST(ResourceManagementTest, MultipleInstancesCleanup) {
    {
        sf::Font font;
        ASSERT_TRUE(font.loadFromFile("Regular.ttf"));
        for (int i = 0; i < 5; ++i) {
            EatingAdultAvo eatingWindow(font, 0); // Create multiple windows
            // Perform operations on each window
        }
    }
    // All windows should be cleaned up without leaking
    SUCCEED(); // Use external tools to verify
}

// Test resource loading for an image
TEST(ResourceManagementTest, LoadValidImage) {
    sf::Texture texture;
    EXPECT_TRUE(texture.loadFromFile("ValidImage.png")); // Should succeed
}

// Test loading an invalid image
TEST(ResourceManagementTest, LoadInvalidImage) {
    sf::Texture texture;
    EXPECT_FALSE(texture.loadFromFile("NonExistentImage.png")); // Should fail
}

// Test cleanup after error in resource loading
TEST(ResourceManagementTest, CleanupAfterFailedLoad) {
    {
        sf::Texture texture;
        // Attempt to load an invalid image
        EXPECT_FALSE(texture.loadFromFile("NonExistentImage.png"));
        // Check that no resource leaks occur
    }
    // If this test passes without error, assume resources cleaned up
    SUCCEED(); // Use external tools to verify
}
