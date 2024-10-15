// test_event_handling.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MockRenderWindow.h"
#include "AdultAvo.h"

using ::testing::_;
using ::testing::Return;

TEST(EventHandlingTest, HandleCloseEvent) {
    MockRenderWindow mockWindow;
    sf::Font font;
    ASSERT_TRUE(font.loadFromFile("Regular.ttf"));
    int trolleyCount = 0;

    AdultAvo adultAvo(font, trolleyCount);

    sf::Event closeEvent;
    closeEvent.type = sf::Event::Closed;

    EXPECT_CALL(mockWindow, pollEvent(_))
        .WillOnce(::testing::DoAll(::testing::SetArgReferee<0>(closeEvent), Return(true)));

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
        .WillOnce(::testing::DoAll(::testing::SetArgReferee<0>(escapeEvent), Return(true)));

    EXPECT_CALL(mockWindow, close()).Times(1);

    adultAvo.handleEvents(&mockWindow);
}
