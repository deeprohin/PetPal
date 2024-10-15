// test_pet_behavior.cpp

#include <gtest/gtest.h>
#include "adult_avo.h"
#include "baby_avo.h"
#include "baby_ghost.h"
#include "adult_ghost.h"

// Test make_sound() for AdultAvo
TEST(PetBehaviorTest, AdultAvoMakeSound) {
    AdultAvo adultAvo;
    testing::internal::CaptureStdout();  // Capture console output
    adultAvo.make_sound();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Adult Avo sound!\n");  // Verify the correct output
}

// Test make_sound() for BabyAvo
TEST(PetBehaviorTest, BabyAvoMakeSound) {
    BabyAvo babyAvo;
    testing::internal::CaptureStdout();
    babyAvo.make_sound();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Baby Avo sound!\n");
}

// Test make_sound() for BabyGhost
TEST(PetBehaviorTest, BabyGhostMakeSound) {
    BabyGhost babyGhost;
    testing::internal::CaptureStdout();
    babyGhost.make_sound();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Baby Ghost sound!\n");
}

// Test make_sound() for AdultGhost
TEST(PetBehaviorTest, AdultGhostMakeSound) {
    AdultGhost adultGhost;
    testing::internal::CaptureStdout();
    adultGhost.make_sound();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Adult Ghost sound!\n");
}

// Test eat() method for BabyAvo
TEST(PetBehaviorTest, BabyAvoEat) {
    sf::Font font;
    font.loadFromFile("Regular.ttf");
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    std::vector<Item> basket;
    
    BabyAvo babyAvo;
    babyAvo.eat(window, font, basket);
    EXPECT_GT(basket.size(), 0);  // Ensure the basket contains items after eating
}
