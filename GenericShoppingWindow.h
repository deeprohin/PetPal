#ifndef GENERIC_SHOPPING_WINDOW_H
#define GENERIC_SHOPPING_WINDOW_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Shopping.h"
#include "Item.h" // Assuming you have an Item structure defined

class GenericShoppingWindow {
public:
    // Constructor: takes Shopping object to fetch items, user coins, and basket
    GenericShoppingWindow(sf::Font& font, int& userCoins, std::vector<Item>& basket, Shopping& shoppingData);
    
    // Destructor
    ~GenericShoppingWindow(); 
    
    // Open the shopping window
    void open();

private:
    sf::RenderWindow* window;
    sf::Font& font;
    int& userCoins;
    std::vector<Item>& basket;
    int trolleyCount;

    sf::Text coinsText;
    sf::Text trolleyText;
    sf::Text insufficientFundsText;
    sf::Texture trolleyTexture;
    sf::Sprite trolleySprite;
    std::vector<Item> items;

    Shopping& shoppingData; // Reference to the Shopping object for item details

    void loadItems();      // Load items from Shopping class
    void handleEvents();   // Handle user input events
    void render();         // Render the shopping window
};

#endif // GENERIC_SHOPPING_WINDOW_H
