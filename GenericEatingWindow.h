#ifndef GENERIC_EATING_WINDOW_H
#define GENERIC_EATING_WINDOW_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Item.h"
#include "BaseItem.h"
#include "EatingShop.h"

class GenericEatingWindow {
public:
    GenericEatingWindow(sf::Font& font, std::vector<std::shared_ptr<BaseItem>>& eatingBasket, EatingShop& eatingShop);

    void open();
    void loadFoodItems();

private:
    sf::RenderWindow window;
    sf::Font& font;
    std::vector<std::shared_ptr<BaseItem>>& basket;
    EatingShop& EatingShopData;
    std::vector<std::shared_ptr<BaseItem>> foodItems;  // Stores food items as shared pointers to BaseItem
};

#endif // GENERIC_EATING_WINDOW_H
