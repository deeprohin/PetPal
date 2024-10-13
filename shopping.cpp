#include "shopping.h"

// Constructor to determine if it's for a baby or an adult
Shopping::Shopping(bool isBaby) {
    if (isBaby) {
        initializeBabyItems();
    } else {
        initializeAdultItems();
    }
}

// Baby items initialization
void Shopping::initializeBabyItems() {
    itemNames = {"Baby Porridge", "Baby Milk", "Baby Pumpkin", "Baby Medicine"};
    itemPrices = {100, 150, 80, 500};
    imagePaths = {
        "Images/Porridge.png",
        "Images/Milk2.png",
        "Images/Pumpkin.png",
        "Images/BabyMedicine.png"
    };
}

// Adult items initialization
void Shopping::initializeAdultItems() {
    itemNames = {"Steak", "Fried Rice", "Curry Chicken", "Boba", "Cold Rolls", "Medicine"};
    itemPrices = {500, 200, 200, 150, 180, 500};
    imagePaths = {
        "Images/Steak.png",
        "Images/FriedRice.png",
        "Images/Curry.png",
        "Images/Boba.png",
        "Images/ColdRolls.png",
        "Images/Medicine.png"
    };
}

// Getter for item names
std::vector<std::string> Shopping::getItemNames() {
    return itemNames;
}

// Getter for image paths
std::vector<std::string> Shopping::getImagePaths() {
    return imagePaths;
}

// Getter for item prices
std::vector<int> Shopping::getItemPrices() {
    return itemPrices;
}
