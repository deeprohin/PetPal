#ifndef EATING_ADULT_AVO_H
#define EATING_ADULT_AVO_H

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "pet_stats.h"
struct ItemList {
  std::string name;
  int price;
  int stock;
  std::shared_ptr<sf::Texture> texture;
  sf::Sprite sprite;
  sf::Text quantityText;
};

class EatingAdultAvo {
 public:
  // Constructor
  EatingAdultAvo(sf::Font& font, ItemList* basket, int& basketSize,
                 int& basketCapacity, int& trolleyCount);

  // Destructor to clean up dynamic memory
  ~EatingAdultAvo();

  // Open the eating window and handle interactions
  void open(PetStats& petStats);

 private:
  sf::Font& font;
  ItemList* basket;
  int& basketSize;
  int& basketCapacity;
  int& trolleyCount;
  sf::RenderWindow* window;  // Pointer for dynamic allocation of RenderWindow
  sf::Texture fridgeTexture;
  sf::Sprite fridgeSprite;
  sf::Text insufficientFundsText;
  std::vector<ItemList> foodItems;

  // Load food items into the eating window
  void loadFoodItems();

  // Handle window events
  void handleEvents(PetStats& petStats);

  // Render the eating window
  void render();

  // Function to play eating animation
  void playEatingAnimation(const std::string& foodName);

  // Helper function to add an item to the basket
  void addToBasket(const ItemList& item);
};

#endif  // EATING_ADULT_AVO_H
