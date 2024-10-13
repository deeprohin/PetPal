#ifndef GENERIC_EATING_WINDOW_H
#define GENERIC_EATING_WINDOW_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "EatingShop.h"
#include "ShoppingBasket.h"
#include "Item.h"

class GenericEatingWindow {
public:
    GenericEatingWindow(sf::Font& font, ShoppingBasket& basket, EatingShop& eatingShopData);
    ~GenericEatingWindow();
    
    void open();

private:
    sf::Font& font;
    ShoppingBasket& basket;          // Reference to ShoppingBasket instance
    EatingShop& eatingShopData;     // Reference to EatingShop instance
    sf::RenderWindow* window;

    sf::Texture fridgeTexture;
    sf::Sprite fridgeSprite;

    sf::Texture trolleyTexture;       // Texture for trolley image
    sf::Sprite trolleySprite;         // Sprite for trolley image
    sf::Text itemCountText;           // Text to show item count

    sf::Text insufficientFundsText;
    std::vector<Item> foodItems;

    void loadFoodItems();
    void handleEvents();
    void render();
    void updateItemCountText();        // Method to update item count text
    void playEatingAnimation(const std::string& foodName);
};

#endif // GENERIC_EATING_WINDOW_H
