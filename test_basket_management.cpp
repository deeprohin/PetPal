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

// Test removing an item from the basket
TEST(BasketTest, RemoveItemFromBasket) {
    std::vector<Item> basket;
    Item apple, banana;
    apple.name = "Apple";
    apple.price = 50;
    banana.name = "Banana";
    banana.price = 30;
    
    basket.push_back(apple);
    basket.push_back(banana);

    basket.pop_back();  // Remove last item (Banana)
    EXPECT_EQ(basket.size(), 1);  // Basket should contain 1 item
    EXPECT_EQ(basket[0].name, "Apple");
}

// Test trying to remove an item from an empty basket
TEST(BasketTest, RemoveItemFromEmptyBasket) {
    std::vector<Item> basket;
    
    EXPECT_NO_THROW(basket.pop_back());  // Ensure no crash or error
    EXPECT_EQ(basket.size(), 0);  // Basket size should still be 0
}

// Test adding multiple items and checking total price
TEST(BasketTest, AddMultipleItemsAndCheckTotal) {
    std::vector<Item> basket;
    Item apple, banana, orange;
    apple.name = "Apple";
    apple.price = 50;
    banana.name = "Banana";
    banana.price = 30;
    orange.name = "Orange";
    orange.price = 40;
    
    basket.push_back(apple);
    basket.push_back(banana);
    basket.push_back(orange);

    int totalPrice = 0;
    for (const auto& item : basket) {
        totalPrice += item.price;
    }
    
    EXPECT_EQ(basket.size(), 3);  // Basket should contain 3 items
    EXPECT_EQ(totalPrice, 120);  // Total price should be the sum of item prices
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

// Test shopping with insufficient funds (coins)
TEST(ShoppingTest, InsufficientFunds) {
    sf::Font font;
    font.loadFromFile("Regular.ttf");
    std::vector<Item> basket;
    int userCoins = 50;  // Set coins to a low value to simulate insufficient funds

    BabyAvo shopWindow(font, userCoins, basket);
    shopWindow.open();  // Simulate shopping

    // The basket should still be empty if no items could be purchased
    EXPECT_EQ(basket.size(), 0);
}

// Test checking if basket is empty after initializing
TEST(BasketTest, EmptyBasketInitialization) {
    std::vector<Item> basket;
    
    EXPECT_EQ(basket.size(), 0);  // Basket should be empty initially
}

// Test shopping with AdultAvo and checking basket contents
TEST(ShoppingTest, AdultAvoShopping) {
    sf::Font font;
    font.loadFromFile("Regular.ttf");
    std::vector<Item> basket;
    int userCoins = 1000;  // AdultAvo starts with more coins

    AdultAvo shopWindow(font, userCoins, basket);
    shopWindow.open();  // Simulate shopping
    
    EXPECT_GT(basket.size(), 0);  // Basket should contain items after shopping
    EXPECT_LT(userCoins, 1000);  // User's coins should be reduced
}

// Test purchasing the same item multiple times
TEST(BasketTest, PurchaseMultipleSameItem) {
    std::vector<Item> basket;
    Item apple;
    apple.name = "Apple";
    apple.price = 50;

    // Add the same item twice
    basket.push_back(apple);
    basket.push_back(apple);

    EXPECT_EQ(basket.size(), 2);  // Basket should contain 2 items
    EXPECT_EQ(basket[0].name, "Apple");
    EXPECT_EQ(basket[1].name, "Apple");
    EXPECT_EQ(basket[0].price, 50);
    EXPECT_EQ(basket[1].price, 50);
}

