#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Shopping.h"
#include "ShoppingBasket.h"

class GenericShoppingWindow {
public:
    // Constructor
    GenericShoppingWindow(sf::Font& font, int& userCoins, ShoppingBasket& basket, Shopping& shoppingData);
    ~GenericShoppingWindow();

    // Open the shopping window
    void open();

private:
    sf::Font& font;              // Reference to font for text
    int& userCoins;              // Reference to user's coin count
    ShoppingBasket& basket;       // Reference to the user's shopping basket
    Shopping& shoppingData;       // Reference to shopping data

    std::vector<Item> items;      // Vector of items available in the shopping window

    sf::Text coinsText;          // Text for displaying user's coins
    sf::Text trolleyText;        // Text for displaying the trolley count
    sf::Text insufficientFundsText; // Text for insufficient funds message
    sf::Sprite trolleySprite;    // Sprite for the trolley
    sf::Texture trolleyTexture;  // Texture for the trolley

    void loadItems();            // Load items into the shopping window
    void handleEvents(sf::RenderWindow& window); // Handle user events
    void render(sf::RenderWindow& window);       // Render the shopping window
};

