#include "GenericEatingWindow.h"
#include "Fooditem.h"
#include <iostream>

GenericEatingWindow::GenericEatingWindow(sf::Font& font, ShoppingBasket& basket, EatingShop& eatingShopData)
    : font(font), basket(basket), eatingShopData(eatingShopData), window(nullptr) {
    loadFoodItems();

    // Initialize UI Elements
    insufficientFundsText.setFont(font);
    insufficientFundsText.setCharacterSize(36);
    insufficientFundsText.setFillColor(sf::Color::Red);
    insufficientFundsText.setPosition(800, 100);
    insufficientFundsText.setString("");

    // Load Fridge Image
    if (!fridgeTexture.loadFromFile("Images/Fridge.png")) {
        std::cerr << "Error: Fridge image not found at Images/Fridge.png" << std::endl;
    }
    fridgeSprite.setTexture(fridgeTexture);
    fridgeSprite.setScale(static_cast<float>(1920) / fridgeTexture.getSize().x,
                          static_cast<float>(1080) / fridgeTexture.getSize().y);
    fridgeSprite.setPosition(0, 0);

    // Load Trolley Image
    if (!trolleyTexture.loadFromFile("Images/Trolley.png")) {
        std::cerr << "Error: Trolley image not found at Images/Trolley.png" << std::endl;
    }
    trolleySprite.setTexture(trolleyTexture);
    trolleySprite.setScale(0.5f, 0.5f); // Scale down if needed
    trolleySprite.setPosition(1700, 50); // Position it in the top right corner

    // Initialize item count text
    itemCountText.setFont(font);
    itemCountText.setCharacterSize(24);
    itemCountText.setFillColor(sf::Color::Black);
    itemCountText.setPosition(1750, 20); // Adjust position for item count
    updateItemCountText(); // Set initial count
}

void GenericEatingWindow::updateItemCountText() {
    itemCountText.setString("Items: " + std::to_string(basket.getSize())); // Update with the current item count
}

GenericEatingWindow::~GenericEatingWindow() {
    delete window;  // Free dynamically allocated window
}

void GenericEatingWindow::open() {
    window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Eating Shop Window");

    while (window->isOpen()) {
        handleEvents();
        render();
    }
}

void GenericEatingWindow::render() {
    window->clear();
    window->draw(fridgeSprite);

    for (const auto& item : foodItems) {
        window->draw(item.sprite);
        window->draw(item.quantityText);
    }

    // Draw trolley and item count
    window->draw(trolleySprite);
    window->draw(itemCountText);

    window->draw(insufficientFundsText);
    window->display();
}

void GenericEatingWindow::handleEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                for (size_t i = 0; i < foodItems.size(); ++i) {
                    if (foodItems[i].sprite.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window)))) {
                        if (foodItems[i].stock > 0) {
                            foodItems[i].stock--;  // Decrement stock
                            std::shared_ptr<BaseItem> itemPtr = std::make_shared<FoodItem>(foodItems[i].name, foodItems[i].price, foodItems[i].stock);
                            basket.addItem(itemPtr);  // Add item to basket
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
