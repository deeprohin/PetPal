#include "eatingShop.h"

// Constructor to determine if it's for a baby or an adult
EatingShop::EatingShop(bool isBaby) {
    if (isBaby) {
        initializeBabyItems();
    } else {
        initializeAdultItems();
    }
}

// Baby items initialization
void EatingShop::initializeBabyItems() {
    itemNames = {"Baby Pumpkin", "Baby Milk", "Baby Porridge", "Baby Medicine"};
    imagePaths = {
        "Images/Pumpkin.png",
        "Images/Milk2.png",
        "Images/Porridge.png",
        "Images/BabyMedicine.png"
    };

    // Initialize baby items with their prices and stock
    items.clear();
    items.push_back(Item("Baby Pumpkin", 5, 10));
    items.push_back(Item("Baby Milk", 3, 15));
    items.push_back(Item("Baby Porridge", 4, 12));
    items.push_back(Item("Baby Medicine", 8, 5));
}

// Adult items initialization
void EatingShop::initializeAdultItems() {
    itemNames = {"Steak", "Fried Rice", "Curry Chicken", "Boba", "Cold Rolls"};
    imagePaths = {
        "Images/Steak.png",
        "Images/FriedRice.png",
        "Images/Curry.png",
        "Images/Boba.png",
        "Images/ColdRolls.png"
    };

    // Initialize adult items with their prices and stock
    items.clear();
    items.push_back(Item("Steak", 20, 8));
    items.push_back(Item("Fried Rice", 12, 10));
    items.push_back(Item("Curry Chicken", 15, 7));
    items.push_back(Item("Boba", 6, 20));
    items.push_back(Item("Cold Rolls", 10, 9));
}

// Getter for item names
std::vector<std::string> EatingShop::getItemNames() {
    return itemNames;
}

// Getter for image paths
std::vector<std::string> EatingShop::getImagePaths() {
    return imagePaths;
}

// Getter for items
std::vector<Item> EatingShop::getItems() const {
    return items;
}
