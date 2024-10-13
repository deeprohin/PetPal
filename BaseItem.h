#ifndef BASEITEM_H
#define BASEITEM_H

#include <SFML/Graphics.hpp>
#include <string>

class BaseItem {
public:
    virtual ~BaseItem() = default;

    virtual std::string getName() const = 0;
    virtual int getPrice() const = 0;
    virtual sf::Sprite& getSprite() = 0;
};

#endif // BASEITEM_H
