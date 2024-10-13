#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "AdultAvoWindow.h"
#include "Item.h"

int main() {
    // Load the font for text rendering
    sf::Font font;
    if (!font.loadFromFile("Images/Regular.ttf")) { // Ensure the correct font file path
        std::cerr << "Error: Font not found!" << std::endl;
        return EXIT_FAILURE;
    }

    // Initialize user coins and basket
    int userCoins = 1000; // Starting coins for the user
    std::vector<Item> basket; // User's shopping basket

    // Create an instance of the shopping window
    AdultAvoShoppingWindow shoppingWindow(font, userCoins, basket);

    // Open the shopping window
    shoppingWindow.open();

    return 0;
}
