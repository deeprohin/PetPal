#ifndef GENERIC_EATING_WINDOW_H
#define GENERIC_EATING_WINDOW_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "EatingShop.h"  // Include the EatingShop header
#include "Item.h"

class GenericEatingWindow {
public:
    // Constructor
    GenericEatingWindow(sf::Font& font, std::vector<Item>& basket, EatingShop& eatingShopData);

    // Destructor
    ~GenericEatingWindow();

    // Open the EatingShop window
    void open();

private:
    sf::Font& font;
    std::vector<Item>& basket;
    EatingShop& eatingShopData; // Reference to EatingShop instance
    sf::RenderWindow* window;

    sf::Texture fridgeTexture;
    sf::Sprite fridgeSprite;
    sf::Text insufficientFundsText;
    std::vector<Item> foodItems;

    void loadFoodItems();
    void handleEvents();
    void render();
    void playEatingAnimation(const std::string& foodName);
};

#endif // GENERIC_EATING_WINDOW_H
