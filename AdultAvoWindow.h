#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Item.h"  // Including the common Item header
// class AdultAvoShoppingWindow
class AdultAvoShoppingWindow {
 public:
  AdultAvoShoppingWindow();
  AdultAvoShoppingWindow(sf::Font& font, int userCoins,
                         std::vector<Item>& basket);  // constructor
  ~AdultAvoShoppingWindow();  // Destructor to clean up allocated memory
  void open();                // function for opening the window
  std::vector<Item> items;    // vector to store the items
  int returnCoins() {         // function to return the coins
    return userCoins;
  }

 private:
  sf::RenderWindow* window;  // Pointer to RenderWindow
  sf::Font& font;
  int userCoins;
  std::vector<Item>& basket;
  int trolleyCount;

  sf::Text coinsText;
  sf::Text trolleyText;
  sf::Text insufficientFundsText;
  sf::Texture trolleyTexture;
  sf::Sprite trolleySprite;

  void loadItems();
  void handleEvents();
  void render();
};
