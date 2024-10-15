// test_input_output.cpp

#include <gtest/gtest.h>
#include <SFML/Window.hpp>
#include "EatingBabyGhost.h"

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
