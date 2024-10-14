#ifndef EATINGSHOP_H
#define EATINGSHOP_H

#include <string>
#include <vector>
#include "Item.h"  // Include the Item class

class EatingShop {
public:
    // Constructor
    EatingShop(bool isBaby);

    // Getters
    std::vector<std::string> getItemNames();
    std::vector<std::string> getImagePaths();

    // Method to get the list of items
    std::vector<Item> getItems() const;

private:
    std::vector<std::string> itemNames;
    std::vector<std::string> imagePaths;

    std::vector<Item> items; // List of Item objects

    void initializeBabyItems();    // For baby eating items
    void initializeAdultItems();   // For adult eating items
};

#endif // EATINGSHOP_H
