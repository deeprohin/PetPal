#include "GenericEatingWindow.h"
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
            if (basket.getSize() == 0) {
                emptyBasketText.setString("Basket is empty!");
                return;
            }

            sf::Vector2i clickPos = sf::Mouse::getPosition(window);
            int x = clickPos.x;
            int y = clickPos.y;

            // Consume the first item in the basket for simplicity
            if (basket.getSize() > 0) {
                auto item = basket.getItems().front(); // Use the getter to access items
                std::cout << "Consumed: " << item->getName() << std::endl;
            }
        }
    }
}

// Render the eating window
void GenericEatingWindow::render(sf::RenderWindow& window) {
    window.clear(sf::Color(245, 245, 220)); // Beige background

    // Draw UI Elements
    window.draw(messageText);
    
    // Display items in the basket
    if (basket.getSize() > 0) {
        std::string itemsList = "Items in basket:\n";
        for (const auto& item : basket.getItems()) { // Use the getter to access items
            itemsList += item->getName() + "\n";
        }
        itemsText.setString(itemsList);
        itemsText.setPosition(20, 100);
        window.draw(itemsText);
    } else {
        emptyBasketText.setString("Basket is empty!");
        window.draw(emptyBasketText);
    }

    window.display();
}
