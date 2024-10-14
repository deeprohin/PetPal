#include "EatingShop.h"

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
}

// Getter for item names
std::vector<std::string> EatingShop::getItemNames() {
    return itemNames;
}

// Getter for image paths
std::vector<std::string> EatingShop::getImagePaths() {
    return imagePaths;
}
