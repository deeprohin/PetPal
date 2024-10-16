#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "ShoppingBasket.h"

class GenericEatingWindow {
 public:
  // Constructor
  GenericEatingWindow(sf::Font& font, ShoppingBasket& basket);
  ~GenericEatingWindow();

  // Open the eating window
  void open();

 private:
  sf::Font& font;          // Reference to font for text
  ShoppingBasket& basket;  // Reference to the user's shopping basket

  sf::Text messageText;      // Text for messages
  sf::Text itemsText;        // Text for displaying items in the basket
  sf::Text emptyBasketText;  // Text for empty basket message

  void handleEvents(sf::RenderWindow& window);  // Handle user events
  void render(sf::RenderWindow& window);        // Render the eating window
};
