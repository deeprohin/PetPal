#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

struct Item {
    std::string name;                      // Name of the item
    int price;                             // Price of the item
    int stock;                             // Current stock of the item
    sf::Sprite sprite;                     // Sprite for the item
    std::shared_ptr<sf::Texture> texture; // Texture for the item
    sf::Text quantityText;                 // Text to display quantity
};

#endif // ITEM_H

