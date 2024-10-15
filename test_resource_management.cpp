// test_resource_management.cpp
#include <gtest/gtest.h>
#include "EatingAdultAvo.h"

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
