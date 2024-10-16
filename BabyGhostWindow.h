#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Item.h"
// babyGhostShoppingWindow class
class BabyGhostShoppingWindow {
 public:
  BabyGhostShoppingWindow(sf::Font& font, int userCoins,
                          std::vector<Item>& basket);  // comstructor
  ~BabyGhostShoppingWindow();              // destructor to free memory
  void open();                             // function to open the window
  int returnCoins() { return userCoins; }  // return coins
 private:
  void loadItems();     // function to laod items
  void handleEvents();  // function to handle events
  void render();        // function to display the function

  sf::RenderWindow* window;  // pointer for RenderWindow
  sf::Font& font;
  int userCoins;
  std::vector<Item>& basket;
  std::vector<Item> items;
  int trolleyCount;

  // UI elements
  sf::Text coinsText;
  sf::Text trolleyText;
  sf::Text insufficientFundsText;

  // trolley image
  sf::Texture trolleyTexture;
  sf::Sprite trolleySprite;
};