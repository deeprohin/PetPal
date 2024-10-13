#include "GenericEatingWindow.h"
#include "Fooditem.h"
#include <iostream>

// Constructor
GenericEatingWindow::GenericEatingWindow(sf::Font& font, ShoppingBasket& basket)
    : font(font), basket(basket) {
    
    // Initialize message text
    messageText.setFont(font);
    messageText.setCharacterSize(36);
    messageText.setFillColor(sf::Color::Black);
    messageText.setPosition(20, 20);
    messageText.setString("Choose an item to eat:");

    emptyBasketText.setFont(font);
    emptyBasketText.setCharacterSize(36);
    emptyBasketText.setFillColor(sf::Color::Red);
    emptyBasketText.setPosition(800, 100);
    emptyBasketText.setString("");

    itemsText.setFont(font); // Ensure this is initialized
    itemsText.setCharacterSize(24);
    itemsText.setFillColor(sf::Color::Black);
}

// Destructor
GenericEatingWindow::~GenericEatingWindow() {
    // No manual deletion needed
}

// Open the eating window
void GenericEatingWindow::open() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Eating Window");

    while (window.isOpen()) {
        handleEvents(window);
        render(window);
    }
}

// Handle user events
void GenericEatingWindow::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                for (size_t i = 0; i < foodItems.size(); ++i) {
                    if (foodItems[i].sprite.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window)))) {
                        if (foodItems[i].stock > 0) {
                            foodItems[i].stock--;  // Decrement stock
                            basket.addItem(foodItems[i]);  // Add item to basket
                            updateItemCountText(); // Update item count
                            std::cout << "Added to basket: " << foodItems[i].name << std::endl;
                        } else {
                            insufficientFundsText.setString("Insufficient stock for: " + foodItems[i].name);
                        }
                    }
                }
            }
        }
    }
}
