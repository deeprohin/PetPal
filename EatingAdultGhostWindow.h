#ifndef EatingAdultGhostWindow_H
#define EatingAdultGhostWindow_H
#include"pet_stats.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include"EatingAdultAvo.h"
// EatingAdultGhostWindow class to handle the interaction with the items
class EatingAdultGhostWindow {
public:
    EatingAdultGhostWindow(sf::Font& font, ItemList* basket, int& basketSize, int& basketCapacity, int& trolleyCount);
    ~EatingAdultGhostWindow(); // Destructor to clean up dynamic memory

    // Open the eating window and handle interactions
    void open(PetStats petStats);

private:
    sf::RenderWindow* window;                  // Pointer for dynamic allocation
    sf::Texture fridgeTexture;                  // Texture for fridge background
    sf::Sprite fridgeSprite;                    // Sprite for fridge background
    sf::Font& font;                             // Font used for text display

    ItemList* basket;                               // Dynamically allocated array for basket items
    int& basketSize;                            // Reference to the current size of the basket
    int& basketCapacity;                        // Reference to the current capacity of the basket
    int& trolleyCount;                          // Reference to the trolley count

    sf::Text insufficientFundsText;             // Text to display insufficient funds message
    std::vector<ItemList> foodItems;                // Vector to hold food items

    // Load food items into the window
    void loadFoodItems();

    // Handle window events like clicking items
    void handleEvents(PetStats petStats);

    // Render the window and items
    void render();

    // Play animation or sound when an item is consumed
    void playEatingAnimation(const std::string& foodName);

    // Helper function to add an item to the basket
    void addToBasket(const ItemList& item);
};

#endif // EatingAdultGhostWindow_H
