#ifndef EATINGBABYAVO_H
#define EATINGBABYAVO_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Item structure to represent a food item
struct Item {
    std::string name;                          // Name of the item
    int price;                                 // Price of the item
    int stock;                                 // Quantity of the item in stock
    std::shared_ptr<sf::Texture> texture;     // Texture of the item image
    sf::Sprite sprite;                         // Sprite to represent the item
    sf::Text quantityText;                     // Text to display item quantity
};

// EatingBabyAvo class to handle the interaction with food items
class EatingBabyAvo {
public:
    EatingBabyAvo(sf::Font& font, Item* basket, int& basketSize, int& basketCapacity, int& trolleyCount);
    ~EatingBabyAvo(); // Destructor to clean up dynamic memory

    // Open the eating window and handle interactions
    void open();

    // Helper function to add an item to the basket
    void addToBasket(const Item& item);

private:
    sf::RenderWindow* window;                  // Pointer for dynamic allocation
    sf::Texture backgroundTexture;              // Texture for background
    sf::Sprite backgroundSprite;                // Sprite for background
    sf::Font& font;                             // Font used for text display

    Item* basket;                               // Pointer to an array of items
    int& basketSize;                            // Reference to the current size of the basket
    int& basketCapacity;                         // Reference to the current capacity of the basket
    int& trolleyCount;                          // Reference to the trolley count

    sf::Text insufficientFundsText;             // Text to display insufficient funds message
    std::vector<Item> foodItems;                // Vector to hold food items

    // Load food items into the window
    void loadFoodItems();

    // Handle window events like clicking items
    void handleEvents();

    // Render the window and items
    void render();

    // Play animation or sound when an item is consumed
    void playEatingAnimation(const std::string& foodName);
};

#endif // EATINGBABYAVO_H
