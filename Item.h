#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "BaseItem.h"

struct Item : public BaseItem {
    std::string name;
    int price;
    int stock;
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
    sf::Text quantityText;

    // Override the virtual functions of BaseItem
    std::string getName() const override { return name; }
    int getPrice() const override { return price; }
    sf::Sprite& getSprite() override { return sprite; }
};

#endif // ITEM_H
