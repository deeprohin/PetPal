// FoodItem.h
#ifndef FOODITEM_H
#define FOODITEM_H

#include "Item.h"
#include <iostream>

class FoodItem : public Item {
public:
    // Constructor
    FoodItem(const std::string& name, int price, int stock)
        : Item(name, price), stock(stock) {}

    // Override display function
    void display() const override {
        std::cout << "Food Item: " << name << ", Price: " << price << ", Stock: " << stock << std::endl;
    }

    // Other member functions as needed
    int getStock() const { return stock; }
    void setStock(int newStock) { stock = newStock; }

private:
    int stock; // Specific to FoodItem
};

#endif // FOODITEM_H
