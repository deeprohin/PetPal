#include "ShoppingBasket.h"
#include <iostream>

ShoppingBasket::ShoppingBasket(int initialCapacity)
    : basketSize(0), basketCapacity(initialCapacity) {
    items = new Item[basketCapacity];
}

ShoppingBasket::~ShoppingBasket() {
    delete[] items;  // Free allocated memory
}

void ShoppingBasket::addItem(const Item& item) {
    if (basketSize >= basketCapacity) {
        resizeBasket();
    }
    items[basketSize] = item;  // Add item to basket
    basketSize++;
}

int ShoppingBasket::getSize() const {
    return basketSize;  // Return current size of the basket
}

void ShoppingBasket::resizeBasket() {
    basketCapacity *= 2;  // Double the capacity
    Item* newItems = new Item[basketCapacity];

    // Copy old items to the new array
    for (int i = 0; i < basketSize; i++) {
        newItems[i] = items[i];
    }

    delete[] items;  // Free old memory
    items = newItems;  // Point to the new array
}
