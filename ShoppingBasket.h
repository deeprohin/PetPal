#ifndef SHOPPINGBASKET_H
#define SHOPPINGBASKET_H

#include <vector>
#include <memory>
#include "Item.h" // Ensure to include the Item header

class ShoppingBasket {
public:
    // Constructor
    ShoppingBasket(int initialCapacity);
    
    // Destructor
    ~ShoppingBasket();

    // Add an item to the basket
    void addItem(std::shared_ptr<Item> item); // Change BaseItem to Item

    // Display items in the basket
    void displayItems() const;

    // Get the current size of the basket
    int getSize() const;

    // Getter for items (optional, can be used to access items externally)
    const std::vector<std::shared_ptr<Item>>& getItems() const;

private:
    std::vector<std::shared_ptr<Item>> items; // Vector to hold items
    int capacity; // Current capacity of the basket
    int size;     // Current size of the basket

    // Resize the basket when full
    void resizeBasket();
};

#endif // SHOPPINGBASKET_H
