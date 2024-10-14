#include "FoodItem.h"

// Constructor: Initialize the base class (Item)
FoodItem::FoodItem(const std::string& name, int price, int stock)
    : Item(name, price), stock(stock) {} // Call the Item constructor

// Getter for stock
int FoodItem::getStock() const {
    return stock;  // Return stock
}

// Setter for stock
void FoodItem::setStock(int newStock) {
    stock = newStock; // Update stock
}

// Override display function (inherited from Item)
void FoodItem::display() const {
    std::cout << "Food Item: " << getName() << ", Price: " << getPrice() << ", Stock: " << getStock() << std::endl;
}
