#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "Item.h" // including the Item header file
#include"pet_stats.h"
class BabyAvo {
public:
    BabyAvo(sf::Font& font, int userCoins, std::vector<Item>& basket);
    ~BabyAvo();  // destructor to clean up allocated memory
    void open();  // opens the shopping window
    int returnCoins(){return userCoins;}
private:
    void loadItems(); // loads items into the window
    void handleEvents(); // handles events
    void render(); // renders the window

    sf::RenderWindow* window; // pointer to the SFML window
    sf::Font& font; // font reference for displaying text
    int userCoins; // reference to the user's coin count
    std::vector<Item>& basket; // reference to the basket
    std::vector<Item> items; // list of items available for purchase
    int trolleyCount; // counter for items in the trolley
    sf::Text coinsText; // text displaying user's coins
    sf::Text trolleyText; // text displaying trolley count
    sf::Text insufficientFundsText; // text displaying insufficient funds message
    sf::Texture trolleyTexture; // texture for the trolley image
    sf::Sprite trolleySprite; // sprite for the trolley image
};

