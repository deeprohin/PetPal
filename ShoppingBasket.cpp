// ShoppingBasket.cpp
#include "ShoppingBasket.h"

// Constructor
ShoppingBasket::ShoppingBasket(int initialCapacity) : capacity(initialCapacity), size(0) {
    items.reserve(capacity); // Reserve space for the initial capacity
}

// Destructor
ShoppingBasket::~ShoppingBasket() {
    // No need for manual deletion; smart pointers handle this automatically
}

// Add an item to the basket
void ShoppingBasket::addItem(std::shared_ptr<BaseItem> item) {
    if (size >= capacity) {
        resizeBasket(); // Resize if the current size reaches capacity
    }
    items.push_back(item); // Use vector to add the item
    size++;
}

// Resize the basket when full
void ShoppingBasket::resizeBasket() {
    capacity *= 2; // Double the capacity
    items.reserve(capacity); // Reserve new capacity
}

// Display items in the basket
void ShoppingBasket::displayItems() const {
    for (const auto& item : items) {
        item->display(); // Use polymorphism to call the display method
    }
}

// Get the current size of the basket
int ShoppingBasket::getSize() const {
    return size;
}
