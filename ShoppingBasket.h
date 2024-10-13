// ShoppingBasket.h
#ifndef SHOPPINGBASKET_H
#define SHOPPINGBASKET_H

#include <vector>
#include <memory>
#include <iostream>
#include "BaseItem.h" // Use the base class

class ShoppingBasket {
public:
    ShoppingBasket(int initialCapacity);
    ~ShoppingBasket();

    void addItem(std::shared_ptr<BaseItem> item); // Use shared_ptr to manage items
    void displayItems() const;
    int getSize() const;

private:
    std::vector<std::shared_ptr<BaseItem>> items; // Use vector of shared pointers
    int capacity;           // Total capacity of the basket
    int size;               // Current number of items in the basket

    void resizeBasket();    // Resize the basket when full
};

#endif // SHOPPINGBASKET_H
