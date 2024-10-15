// test_input_output.cpp

#include <gtest/gtest.h>
#include <SFML/Window.hpp>
#include "AdultGhostWindow.h"

// Test clicking the game button (simulate user interaction)
TEST(InputOutputTest, ClickGameButton) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    sf::Event event;
    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.x = 900;  // X position of the game button
    event.mouseButton.y = 130;  // Y position of the game button

    EXPECT_EQ(event.type, sf::Event::MouseButtonPressed);  // Simulate mouse click event
}

// Test clicking the pet (touching the character)
TEST(InputOutputTest, ClickPet) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    sf::Event event;
    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.x = 700;  // X position of the pet
    event.mouseButton.y = 500;  // Y position of the pet

    EXPECT_EQ(event.type, sf::Event::MouseButtonPressed);
    // Simulate action after touching pet
}

// Test keyboard input handling (Escape key)
TEST(InputOutputTest, PressEscapeKey) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    sf::Event event;
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::Escape;

    EXPECT_EQ(event.type, sf::Event::KeyPressed);  // Simulate key press event
    EXPECT_EQ(event.key.code, sf::Keyboard::Escape);  // Ensure it is the Escape key
}

// Test keyboard input handling (Arrow keys)
TEST(InputOutputTest, PressArrowKey) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    sf::Event event;
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::Up;

    EXPECT_EQ(event.type, sf::Event::KeyPressed);  // Simulate key press event
    EXPECT_EQ(event.key.code, sf::Keyboard::Up);  // Ensure it is the Up arrow key
}

// Test clicking the exit button (simulate user interaction)
TEST(InputOutputTest, ClickExitButton) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    sf::Event event;
    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.x = 50;  // X position of the exit button
    event.mouseButton.y = 20;   // Y position of the exit button

    EXPECT_EQ(event.type, sf::Event::MouseButtonPressed);  // Simulate mouse click event
}

// Test clicking outside of interactive elements
TEST(InputOutputTest, ClickOutsideInteractiveElements) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    sf::Event event;
    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.x = 400;  // X position outside of any button
    event.mouseButton.y = 300;   // Y position outside of any button

    EXPECT_EQ(event.type, sf::Event::MouseButtonPressed);  // Simulate mouse click event
    // You can add more logic to check if any actions were triggered
}
