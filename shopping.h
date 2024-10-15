#ifndef SHOPPING_H
#define SHOPPING_H

#include <string>
#include <vector>

class Shopping {
 public:
  // Constructor
  Shopping(bool isBaby);

  // Getters
  std::vector<std::string> getItemNames();
  std::vector<std::string> getImagePaths();
  std::vector<int> getItemPrices();

 private:
  std::vector<std::string> itemNames;
  std::vector<std::string> imagePaths;
  std::vector<int> itemPrices;

  void initializeBabyItems();   // For baby shopping items
  void initializeAdultItems();  // For adult shopping items
};

#endif
