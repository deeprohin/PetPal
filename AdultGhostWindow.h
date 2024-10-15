#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Item.h"

class AdultGhostWindow {
public:
    AdultGhostWindow(sf::Font& font, int userCoins, std::vector<Item>& basket);
    ~AdultGhostWindow();
    void open();
    int returnCoins(){return userCoins;}
private:
    void loadItems();
    void handleEvents();
    void render();

    sf::RenderWindow* window;// The shopping window
    sf::Font& font; // Reference to the font
    int userCoins; // Reference to user's coins
    std::vector<Item>& basket; // Reference to the user's basket
    std::vector<Item> items; // List of items available for purchase
    int trolleyCount; // Number of items in the trolley

    sf::Text coinsText; // Text to display user coins
    sf::Text trolleyText; // Text to display trolley count
    sf::Text insufficientFundsText; // Text to display insufficient funds message
    sf::Texture trolleyTexture; // Texture for the trolley image
    sf::Sprite trolleySprite; // Sprite for the trolley image
};

