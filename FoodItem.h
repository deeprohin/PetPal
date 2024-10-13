// FoodItem.h
#ifndef FOODITEM_H
#define FOODITEM_H

#include "BaseItem.h"

class FoodItem : public BaseItem {
public:
    FoodItem(const std::string& name, int price, int stock);
    std::string getName() const override;
    int getPrice() const override;
    int getStock() const override;
    void setStock(int newStock) override;
    void display() const override;

private:
    std::string name;
    int price;
    int stock; // Stock specific to food items
    std::shared_ptr<sf::Texture> texture; // Keep your texture
    sf::Sprite sprite; // Keep your sprite
};

#endif // FOODITEM_H

