#ifndef ADULT_AVO_WINDOW_H
#define ADULT_AVO_WINDOW_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Item.h" // Include the common Item header

class AdultAvoShoppingWindow {
public:
    AdultAvoShoppingWindow(sf::Font& font, int& userCoins, std::vector<Item>& basket);
    ~AdultAvoShoppingWindow(); // Destructor to clean up allocated memory
    void open();

private:
    sf::RenderWindow* window; // Pointer to RenderWindow
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

    void loadItems();
    void handleEvents();
    void render();
};

#endif // ADULT_AVO_WINDOW_H
