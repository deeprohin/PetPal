#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <sstream>


class Item {
public:
    // Constructor
    Item() : name(""), price(0), stock(0), texture(std::make_shared<sf::Texture>()) {
    // You can initialize default values if needed
}
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
    std::string name; // Name of the item
        int price;        // Price of the item
        int stock; 

    
};

// Overload operator<< for writing Item to an ostream
inline std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << item.name << "," << item.stock; // CSV format
return os;
}

#endif // ITEM_H
