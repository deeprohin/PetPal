// test_event_handling.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MockRenderWindow.h"
#include "AdultAvo.h"
#include "BabyAvo.h"
#include "BabyGhost.h"
#include "AdultGhost.h"

using ::testing::_;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::SetArgReferee;

TEST(EventHandlingTest, HandleCloseEvent) {
    MockRenderWindow mockWindow;
    sf::Font font;
    ASSERT_TRUE(font.loadFromFile("Regular.ttf"));
    int trolleyCount = 0;

    AdultAvo adultAvo(font, trolleyCount);

    sf::Event closeEvent;
    closeEvent.type = sf::Event::Closed;

    EXPECT_CALL(mockWindow, pollEvent(_))
        .WillOnce(DoAll(SetArgReferee<0>(closeEvent), Return(true)));

    EXPECT_CALL(mockWindow, close()).Times(1);

    adultAvo.handleEvents(&mockWindow);
}

TEST(EventHandlingTest, HandleEscapeKeyEvent) {
    MockRenderWindow mockWindow;
    sf::Font font;
    ASSERT_TRUE(font.loadFromFile("Regular.ttf"));
    int trolleyCount = 0;

    AdultAvo adultAvo(font, trolleyCount);

    sf::Event escapeEvent;
    escapeEvent.type = sf::Event::KeyPressed;
    escapeEvent.key.code = sf::Keyboard::Escape;

    EXPECT_CALL(mockWindow, pollEvent(_))
        .WillOnce(DoAll(SetArgReferee<0>(escapeEvent), Return(true)));

    EXPECT_CALL(mockWindow, close()).Times(1);

    adultAvo.handleEvents(&mockWindow);
}

// Test handling of mouse button pressed event
TEST(EventHandlingTest, HandleMouseButtonPressedEvent) {
    MockRenderWindow mockWindow;
    sf::Font font;
    ASSERT_TRUE(font.loadFromFile("Regular.ttf"));
    int trolleyCount = 0;

    AdultAvo adultAvo(font, trolleyCount);

    sf::Event mouseEvent;
    mouseEvent.type = sf::Event::MouseButtonPressed;
    mouseEvent.mouseButton.button = sf::Mouse::Left;
    mouseEvent.mouseButton.x = 100; // example coordinates
    mouseEvent.mouseButton.y = 150;

    EXPECT_CALL(mockWindow, pollEvent(_))
        .WillOnce(DoAll(SetArgReferee<0>(mouseEvent), Return(true)));

    adultAvo.handleEvents(&mockWindow);

    // Validate if the event was handled correctly (custom checks can be added here)
}

// Test handling of key press event for BabyAvo
TEST(EventHandlingTest, BabyAvoHandleKeyPress) {
    MockRenderWindow mockWindow;
    sf::Font font;
    ASSERT_TRUE(font.loadFromFile("Regular.ttf"));
    int trolleyCount = 0;

    BabyAvo babyAvo(font, trolleyCount);

    sf::Event keyPressEvent;
    keyPressEvent.type = sf::Event::KeyPressed;
    keyPressEvent.key.code = sf::Keyboard::Space;

    EXPECT_CALL(mockWindow, pollEvent(_))
        .WillOnce(DoAll(SetArgReferee<0>(keyPressEvent), Return(true)));

    babyAvo.handleEvents(&mockWindow);

    // Check if the key press was handled (specific checks or custom logic can be added)
}

// Test handling resize event for BabyGhost
TEST(EventHandlingTest, BabyGhostHandleResizeEvent) {
    MockRenderWindow mockWindow;
    sf::Font font;
    ASSERT_TRUE(font.loadFromFile("Regular.ttf"));
    int trolleyCount = 0;

    BabyGhost babyGhost(font, trolleyCount);

    sf::Event resizeEvent;
    resizeEvent.type = sf::Event::Resized;
    resizeEvent.size.width = 800;
    resizeEvent.size.height = 600;

    EXPECT_CALL(mockWindow, pollEvent(_))
        .WillOnce(DoAll(SetArgReferee<0>(resizeEvent), Return(true)));

    babyGhost.handleEvents(&mockWindow);

    // Add checks to validate the resize event if necessary
}

// Test handling joystick connected event for AdultGhost
TEST(EventHandlingTest, AdultGhostHandleJoystickConnected) {
    MockRenderWindow mockWindow;
    sf::Font font;
    ASSERT_TRUE(font.loadFromFile("Regular.ttf"));
    int trolleyCount = 0;

    AdultGhost adultGhost(font, trolleyCount);

    sf::Event joystickEvent;
    joystickEvent.type = sf::Event::JoystickConnected;
    joystickEvent.joystickConnect.joystickId = 0;

    EXPECT_CALL(mockWindow, pollEvent(_))
        .WillOnce(DoAll(SetArgReferee<0>(joystickEvent), Return(true)));

    adultGhost.handleEvents(&mockWindow);

    // Add additional checks to validate the joystick event handling
}

// Test handling of window focus lost event
TEST(EventHandlingTest, HandleWindowFocusLost) {
    MockRenderWindow mockWindow;
    sf::Font font;
    ASSERT_TRUE(font.loadFromFile("Regular.ttf"));
    int trolleyCount = 0;

    AdultAvo adultAvo(font, trolleyCount);

    sf::Event focusEvent;
    focusEvent.type = sf::Event::LostFocus;

    EXPECT_CALL(mockWindow, pollEvent(_))
        .WillOnce(DoAll(SetArgReferee<0>(focusEvent), Return(true)));

    adultAvo.handleEvents(&mockWindow);

    // Add additional checks if you want to handle lost focus (like pausing the game)
}
