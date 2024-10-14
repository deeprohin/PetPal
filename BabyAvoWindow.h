#ifndef BABYAVO_H
#define BABYAVO_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "Item.h" // Include the Item header file

class BabyAvo {
public:
    BabyAvo(sf::Font& font, int userCoins, std::vector<Item>& basket);
    ~BabyAvo();  // Destructor to clean up allocated memory
    void open();  // Opens the shopping window
    int returnCoins(){return userCoins;}
private:
    void loadItems(); // Loads items into the window
    void handleEvents(); // Handles events
    void render(); // Renders the window

    sf::RenderWindow* window; // Pointer to the SFML window
    sf::Font& font; // Font reference for displaying text
    int userCoins; // Reference to the user's coin count
    std::vector<Item>& basket; // Reference to the basket
    std::vector<Item> items; // List of items available for purchase
    int trolleyCount; // Counter for items in the trolley
    sf::Text coinsText; // Text displaying user's coins
    sf::Text trolleyText; // Text displaying trolley count
    sf::Text insufficientFundsText; // Text displaying insufficient funds message
    sf::Texture trolleyTexture; // Texture for the trolley image
    sf::Sprite trolleySprite; // Sprite for the trolley image
};

#endif // BABYAVO_H
