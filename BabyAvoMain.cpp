#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "BabyAvo.h"

int main() {
    // Load font for displaying text
    sf::Font font;
    if (!font.loadFromFile("Images/Regular.ttf")) { // Adjust the font path as necessary
        std::cerr << "Error loading font!" << std::endl;
        return EXIT_FAILURE;
    }

    int userCoins = 500; // Example starting coins
    std::vector<Item> basket; // Basket to hold purchased items

    // Create BabyAvo instance
    BabyAvo shop(font, userCoins, basket);
    shop.open(); // Open the shopping window

    return 0;
}
