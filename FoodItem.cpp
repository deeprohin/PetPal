// FoodItem.cpp
#include "FoodItem.h"
#include <iostream>

FoodItem::FoodItem(const std::string& name, int price, int stock)
    : name(name), price(price), stock(stock) {}

std::string FoodItem::getName() const {
    return name;
}

int FoodItem::getPrice() const {
    return price;
}

int FoodItem::getStock() const {
    return stock;
}

void FoodItem::setStock(int newStock) {
    stock = newStock; // Update stock
}

void FoodItem::display() const {
    std::cout << "Food Item: " << name << ", Price: " << price << ", Stock: " << stock << std::endl;
}
