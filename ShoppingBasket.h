#ifndef SHOPPINGBASKET_H
#define SHOPPINGBASKET_H

#include <vector>
#include "Item.h"

class ShoppingBasket {
public:
    ShoppingBasket(int initialCapacity);
    ~ShoppingBasket();
    
    void addItem(const Item& item);
    int getSize() const;

private:
    Item* items;
    int basketSize;
    int basketCapacity;

    void resizeBasket();  // Resize the basket
};

#endif // SHOPPINGBASKET_H
