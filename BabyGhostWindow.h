#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Item.h"

class BabyGhostShoppingWindow {
public:
    BabyGhostShoppingWindow(sf::Font& font, int userCoins, std::vector<Item>& basket);
    ~BabyGhostShoppingWindow(); // Destructor to free memory
    void open();

private:
    void loadItems();
    void handleEvents();
    void render();

    sf::RenderWindow* window; // Raw pointer for RenderWindow
    sf::Font& font;
    int userCoins;
    std::vector<Item>& basket;
    std::vector<Item> items;
    int trolleyCount;

    // UI elements
    sf::Text coinsText;
    sf::Text trolleyText;
    sf::Text insufficientFundsText;

    // Trolley image
    sf::Texture trolleyTexture;
    sf::Sprite trolleySprite;
};