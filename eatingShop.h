#ifndef EATINGSHOP_H
#define EATINGSHOP_H

#include <string>
#include <vector>

class EatingShop {
public:
    // Constructor
    EatingShop(bool isBaby);

    // Getters
    std::vector<std::string> getItemNames();
    std::vector<std::string> getImagePaths();

private:
    std::vector<std::string> itemNames;
    std::vector<std::string> imagePaths;

    void initializeBabyItems();    // For baby eating items
    void initializeAdultItems();   // For adult eating items
};

#endif // EATINGSHOP_H
