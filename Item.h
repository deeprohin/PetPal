#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <string>

struct Item {
    std::string name;
    int price;
    int stock;
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
    sf::Text quantityText;
};

#endif // ITEM_H
