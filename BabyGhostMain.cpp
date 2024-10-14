#include <SFML/Graphics.hpp>
#include "BabyGhostWindow.h"
#include "Item.h"
#include <vector>

int main() {
    sf::Font font;
    if (!font.loadFromFile("Images/Regular.ttf")) {
        return -1;
    }

    int userCoins = 1000; // Example starting coin amount
    std::vector<Item> basket;

    // Create a dynamically allocated BabyGhostShoppingWindow
    BabyGhostShoppingWindow* shoppingWindow = new BabyGhostShoppingWindow(font, userCoins, basket);

    // Open the window
    shoppingWindow->open();

    // Once done, make sure to delete it to avoid memory leaks
    delete shoppingWindow;

    return 0;
}
