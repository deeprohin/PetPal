#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

class Item {
public:
    // Constructor
    Item(const std::string& name, int price, int stock);

    // Getters
    std::string getName() const;
    int getPrice() const;
    int getStock() const;

    // Methods
    void setStock(int stock);
    void display() const; // For demonstration purposes

    // SFML elements
    sf::Sprite sprite; // Sprite to display the item
    std::shared_ptr<sf::Texture> texture; // Texture for the sprite

private:
    std::string name; // Name of the item
    int price;        // Price of the item
    int stock;       // Number of items in stock
};

#endif // ITEM_H
