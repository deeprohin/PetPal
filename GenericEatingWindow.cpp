#include "GenericEatingWindow.h"
#include <iostream>

// Constructor
GenericEatingWindow::GenericEatingWindow(sf::Font& font, std::vector<Item>& basket, EatingShop& eatingShopData)
    : font(font), basket(basket), eatingShopData(eatingShopData), window(nullptr) {
    // Load food items from the EatingShop class
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
        // Handle loading error gracefully
    }
    fridgeSprite.setTexture(fridgeTexture);
    fridgeSprite.setScale(static_cast<float>(1920) / fridgeTexture.getSize().x,
                          static_cast<float>(1080) / fridgeTexture.getSize().y);
    fridgeSprite.setPosition(0, 0);
}

// Destructor
GenericEatingWindow::~GenericEatingWindow() {
    delete window; // Clean up the window object
}

// Load food items from the EatingShop class
void GenericEatingWindow::loadFoodItems() {
    std::vector<std::string> itemNames = eatingShopData.getItemNames();
    std::vector<std::string> imagePaths = eatingShopData.getImagePaths();

    // Load each food item and store in the foodItems vector
    for (size_t i = 0; i < itemNames.size(); ++i) {
        Item item;
        item.name = itemNames[i];
        item.price = 0;  // Assuming no price is needed for EatingShop items
        item.stock = 1;   // Default stock value, assuming it's available

        // Load texture
        item.texture = std::make_shared<sf::Texture>();
        if (!item.texture->loadFromFile(imagePaths[i])) {
            std::cerr << "Error: " << itemNames[i] << " image not found at " << imagePaths[i] << std::endl;
            continue; // Skip this item if texture loading fails
        }

        // Set texture to sprite
        item.sprite.setTexture(*item.texture);

        // Scale sprite
        float scaleX = 150.0f / item.texture->getSize().x;
        float scaleY = 150.0f / item.texture->getSize().y;
        item.sprite.setScale(scaleX, scaleY);

        // Set position based on grid layout
        int numCols = 4; // Adjust based on the number of items
        int numRows = (itemNames.size() + numCols - 1) / numCols;
        int horizontalSpacing = 200;
        int verticalSpacing = 250;
        int startX = (1920 - (150 * numCols + horizontalSpacing * (numCols - 1))) / 2;
        int startY = (1080 - (150 * numRows + verticalSpacing * (numRows - 1))) / 2;

        int row = i / numCols;
        int col = i % numCols;
        int xPos = startX + col * (150 + horizontalSpacing);
        int yPos = startY + row * (150 + verticalSpacing);
        item.sprite.setPosition(xPos, yPos);

        // Initialize quantity text
        sf::Text quantity;
        quantity.setFont(font);
        quantity.setCharacterSize(24);
        quantity.setFillColor(sf::Color::Black);
        quantity.setPosition(xPos, yPos + item.sprite.getGlobalBounds().height + 10);
        quantity.setString("Quantity: " + std::to_string(item.stock));
        // Assuming you have a text member in Item, else manage separately

        foodItems.push_back(item);
    }
}

// Open the EatingShop window
void GenericEatingWindow::open() {
    window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Eating Shop Window");
    
    while (window->isOpen()) {
        handleEvents();
        render();
    }
}

// Handle user events (e.g., mouse clicks)
void GenericEatingWindow::handleEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i clickPos = sf::Mouse::getPosition(*window);
            int x = clickPos.x;
            int y = clickPos.y;

            // Reset insufficient funds message
            insufficientFundsText.setString("");

            // Check if any food item was clicked
            for (auto& food : foodItems) {
                if (food.sprite.getGlobalBounds().contains(static_cast<float>(x), static_cast<float>(y))) {
                    if (food.stock > 0) {
                        // Simulate eating the food item
                        food.stock--;
                        basket.push_back(food);

                        // Update quantity display
                        // Assuming you have a quantityText member in Item, else manage separately

                        // Play eating animation
                        playEatingAnimation(food.name);

                        std::cout << "Ate: " << food.name << std::endl;
                    }
                    else {
                        insufficientFundsText.setString("NO MORE " + food.name + " LEFT");
                        std::cout << "No more " << food.name << " left to eat." << std::endl;
                    }
                }
            }
        }
    }
}

// Render the EatingShop window
void GenericEatingWindow::render() {
    window->clear(sf::Color(245, 245, 220)); // Beige background

    // Draw Background
    window->draw(fridgeSprite);

    // Draw Insufficient Funds Message
    window->draw(insufficientFundsText);

    // Draw Food Items and Quantity
    for (const auto& food : foodItems) {
        window->draw(food.sprite);
        // Assuming you have quantityText as part of Item, else manage separately
    }

    window->display();
}

// Play eating animation (Placeholder)
void GenericEatingWindow::playEatingAnimation(const std::string& foodName) {
    std::cout << "Playing eating animation for: " << foodName << std::endl;
    // Implement actual animation or sound effects here
}
