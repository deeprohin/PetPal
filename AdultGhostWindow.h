#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "Item.h"
// adult ghost class
class AdultGhostWindow {
 public:
  AdultGhostWindow(sf::Font& font, int userCoins,
                   std::vector<Item>& basket);  // constructor with paramters
  ~AdultGhostWindow();                          // destructor
  void open();                                  // function tp open window
  int returnCoins() { return userCoins; }       // function to return coins
 private:
  void loadItems();     // function to load items
  void handleEvents();  // function to handle all the events
  void render();        // function to render all teh stuff to the screen

  sf::RenderWindow* window;   // The shopping window
  sf::Font& font;             // Reference to the font
  int userCoins;              // Reference to user's coins
  std::vector<Item>& basket;  // Reference to the user's basket
  std::vector<Item> items;    // List of items available for purchase
  int trolleyCount;           // Number of items in the trolley

  sf::Text coinsText;              // Text to display user coins
  sf::Text trolleyText;            // Text to display trolley count
  sf::Text insufficientFundsText;  // Text to display insufficient funds message
  sf::Texture trolleyTexture;      // Texture for the trolley image
  sf::Sprite trolleySprite;        // Sprite for the trolley image
};
