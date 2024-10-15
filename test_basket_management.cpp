// test_basket_management.cpp

#include <gtest/gtest.h>
#include "Item.h"
#include "BabyAvoWindow.h"
#include "AdultAvoWindow.h"

// Test adding an item to the basket
TEST(BasketTest, AddItemToBasket) {
    std::vector<Item> basket;
    Item apple;
    apple.name = "Apple";
    apple.price = 50;
    
    basket.push_back(apple);
    EXPECT_EQ(basket.size(), 1);  // Basket should contain 1 item
    EXPECT_EQ(basket[0].name, "Apple");
    EXPECT_EQ(basket[0].price, 50);
}

// Test basket when shopping with BabyAvo
TEST(ShoppingTest, BabyAvoShopping) {
    sf::Font font;
    font.loadFromFile("Regular.ttf");
    std::vector<Item> basket;
    int userCoins = 500;

    BabyAvo shopWindow(font, userCoins, basket);
    shopWindow.open();  // Simulate shopping
    EXPECT_LT(userCoins, 500);  // Check that coins have been reduced after shopping
    EXPECT_GT(basket.size(), 0);  // Basket should contain items after shopping
}
