#include <SFML/Graphics.hpp>
#include "EatingBabyGhost.h"
#include <vector>
#include <iostream>

int main() {
    // Create an SFML font object
    sf::Font font;
    if (!font.loadFromFile("Images/Regular.ttf")) { // Ensure the font file exists in the correct path
        std::cerr << "Error loading font!" << std::endl;
        return 1;
    }

    // Initial capacity for the basket
    int basketCapacity = 10; // Starting with capacity for 10 items
    int basketSize = 0;      // Current number of items in the basket

    // Dynamically allocate the basket array
    Item* basket = new Item[basketCapacity];

    // Initialize the basket with initial stock for each item
    std::vector<std::string> initialItems = {"Baby Milk", "Baby Porridge", "Yoghurt", "Baby Medicine"};
    std::vector<int> initialPrices = {50, 30, 70, 500};
    std::vector<int> initialStocks = {5, 5, 5, 5};

    for (size_t i = 0; i < initialItems.size(); ++i) {
        basket[basketSize].name = initialItems[i];
        basket[basketSize].price = initialPrices[i];
        basket[basketSize].stock = initialStocks[i];
        basket[basketSize].texture = nullptr; // Will be loaded in EatingBabyGhost
        basket[basketSize].sprite = sf::Sprite();
        basket[basketSize].quantityText = sf::Text();
        basketSize++;
    }

    // Initialize the trolley count (starts at 0)
    int trolleyCount = 0;

    // Create an instance of the EatingBabyGhost class
    EatingBabyGhost eatingWindow(font, basket, basketSize, basketCapacity, trolleyCount);

    // Open the window and run the application
    eatingWindow.open();

    // Clean up dynamically allocated memory
    delete[] basket;

    return 0;
}
