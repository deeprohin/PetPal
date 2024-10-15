#include "EatingAdultGhostWindow.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include "pet_stats.h"

// Constructor
EatingAdultGhostWindow::EatingAdultGhostWindow(sf::Font& font, ItemList* basket, int& basketSize, int& basketCapacity, int& trolleyCount)
    : font(font), basket(basket), basketSize(basketSize), basketCapacity(basketCapacity), trolleyCount(trolleyCount) {
    
    // Dynamically create a RenderWindow
    window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Eating Ghost Window");

    // Load fridge background image
    if (!fridgeTexture.loadFromFile("Images/Fridge.png")) {
        std::cerr << "Error: Fridge image not found!" << std::endl;
        exit(1);
    }
    fridgeSprite.setTexture(fridgeTexture);
    fridgeSprite.setScale(
        static_cast<float>(1920) / fridgeTexture.getSize().x, // Scale to fit width
        static_cast<float>(1080) / fridgeTexture.getSize().y  // Scale to fit height
    );
    fridgeSprite.setPosition(0, 0); // Set position to cover the window

    // Initialize insufficient funds text
    insufficientFundsText.setFont(font);
    insufficientFundsText.setCharacterSize(36);
    insufficientFundsText.setFillColor(sf::Color::Red);
    insufficientFundsText.setPosition(800, 100);
    insufficientFundsText.setString(""); // Initially empty

    // Load food items
    loadFoodItems();
}

// Destructor to clean up dynamic memory
EatingAdultGhostWindow::~EatingAdultGhostWindow() {
    // Clean up the dynamically allocated window
    delete window;
}

// Load food items into the eating window
void EatingAdultGhostWindow::loadFoodItems() {
    // Read stock data from pet_stats.txt
    std::unordered_map<std::string, int> stockData;
    std::ifstream stockFile("pet_stats.txt");
    if (!stockFile.is_open()) {
        std::cerr << "Error: Unable to open pet_stats.txt!" << std::endl;
        exit(1);
    }

    std::string stockLine;
    while (std::getline(stockFile, stockLine)) {
        std::istringstream iss(stockLine);
        std::string itemName;
        int stock;

        std::string lastWord;
        while (iss >> lastWord) {
            itemName += (itemName.empty() ? "" : " ") + lastWord; // Rebuild item name
        }

        size_t lastSpacePos = itemName.find_last_of(' ');
        if (lastSpacePos != std::string::npos) {
            stock = std::stoi(itemName.substr(lastSpacePos + 1));
            itemName = itemName.substr(0, lastSpacePos);
        } else {
            stock = 0; // Default to 0
        }

        stockData[itemName] = stock;
    }
    
    std::vector<std::string> itemNames = {"Chicken", "Milk", "Apple", "Medicine", "Pizza", "Fish"};
    std::vector<int> itemPrices = {100, 50, 50, 500, 70, 70};
    std::vector<std::string> imagePaths = {
        "Images/Chicken.png", 
        "Images/Milk.png", 
        "Images/Apple.png", 
        "Images/Medicine.png", 
        "Images/Pizza.png", 
        "Images/Fish.png"
    };

    // Define grid layout parameters
    const int columns = 3;   // Number of columns
    const int rows = 3;      // Number of rows
    const float imageSize = 150.0f; // Fixed size for each image
    const float horizontalSpacing = 50.0f; // Space between images horizontally
    const float verticalSpacing = 50.0f;   // Space between images vertically
    const float startX = (1920 - (columns * imageSize + (columns - 1) * horizontalSpacing)) / 2.0f; // Center the grid horizontally
    const float startY = (1080 - (rows * imageSize + (rows - 1) * verticalSpacing)) / 2.0f; // Center the grid vertically

    // Load each food item
    for (size_t i = 0; i < itemNames.size(); ++i) {
        ItemList item;
        item.name = itemNames[i];
        item.price = itemPrices[i];
        item.stock = stockData.count(itemNames[i]) ? stockData[itemNames[i]] : 0; // Initialize stock to 5 or any desired number

        // Load texture into shared_ptr
        item.texture = std::make_shared<sf::Texture>();
        if (!item.texture->loadFromFile(imagePaths[i])) {
            std::cerr << "Error: " << itemNames[i] << " image not found at " << imagePaths[i] << std::endl;
            exit(1);
        }

        // Set texture to sprite and scale it
        item.sprite.setTexture(*item.texture);
        item.sprite.setScale(imageSize / item.sprite.getLocalBounds().width, imageSize / item.sprite.getLocalBounds().height); // Scale to fixed size

        // Calculate grid position
        int row = i / columns;
        int col = i % columns;
        float xPosition = startX + col * (imageSize + horizontalSpacing);
        float yPosition = startY + row * (imageSize + verticalSpacing);
        item.sprite.setPosition(xPosition, yPosition);

        // Initialize quantity text for each item
        item.quantityText.setFont(font);
        item.quantityText.setCharacterSize(28); // Slightly larger font size
        item.quantityText.setFillColor(sf::Color::Black);
        // Position the text below the sprite
        item.quantityText.setPosition(
            xPosition,
            yPosition + item.sprite.getGlobalBounds().height + 5 // Increased spacing below the image
        );
        item.quantityText.setString("Quantity: " + std::to_string(item.stock));

        foodItems.push_back(item);
    }
}

// Open the eating window and handle interactions
void EatingAdultGhostWindow::open(PetStats& petStats) {
    while (window->isOpen()) {
        handleEvents(petStats);
        render();
    }
}

// Handle window events
void EatingAdultGhostWindow::handleEvents(PetStats& petStats) {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        // Check for the Esc key press to close the window
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            window->close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i clickPos = sf::Mouse::getPosition(*window);
            int x = clickPos.x;
            int y = clickPos.y;

            // Reset the insufficient funds message
            insufficientFundsText.setString("");

            // Check if any food item was clicked
            for (auto& item : foodItems) {
                sf::FloatRect bounds = item.sprite.getGlobalBounds();
                if (bounds.contains(static_cast<float>(x), static_cast<float>(y))) {
                    // Find the item in the basket
                    petStats.maxHunger();
                    auto it = std::find_if(basket, basket + basketSize, [&item](const ItemList& basketItem) {
                        return basketItem.name == item.name;
                    });

                    // Check stock directly from foodItems
                    if (item.stock > 0) {
                        // Simulate eating the food item
                        item.stock--; // Decrease stock from the foodItems
                        trolleyCount++; // Increase trolley count
                        playEatingAnimation(item.name);
                        std::cout << "Ate: " << item.name << std::endl;

                        // Update the quantity display for this item
                        item.quantityText.setString("Quantity: " + std::to_string(item.stock));
                    } else {
                        insufficientFundsText.setString("NEED TO BUY MORE");
                    }
                }
            }
        }
    }
}


// Render the eating window
void EatingAdultGhostWindow::render() {
    window->clear(sf::Color(245, 245, 220));  // Set background color to beige

    // Draw the fridge sprite
    window->draw(fridgeSprite);
    
    window->draw(insufficientFundsText); // Draw the insufficient funds message

    // Draw each food item
    for (const auto& item : foodItems) {
        window->draw(item.sprite);
        window->draw(item.quantityText);
    }

    window->display();  // Display the drawn content
}

// Play an animation or sound for consuming food (not implemented in this example)
void EatingAdultGhostWindow::playEatingAnimation(const std::string& foodName) {
    // Placeholder for animation or sound playing
}

// Add item to the basket (not implemented in this example)
void EatingAdultGhostWindow::addToBasket(const ItemList& item) {
    // Placeholder for adding item to basket logic
}