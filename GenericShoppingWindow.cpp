#include "GenericShoppingWindow.h"
#include <iostream>

// Constructor
GenericShoppingWindow::GenericShoppingWindow(sf::Font& font, int& userCoins, std::vector<Item>& basket, Shopping& shoppingData)
    : font(font), userCoins(userCoins), basket(basket), shoppingData(shoppingData), trolleyCount(0) {
    // Initialize the shopping window and load items from the Shopping class
    loadItems();

    // Initialize UI Elements
    coinsText.setFont(font);
    coinsText.setCharacterSize(36);
    coinsText.setFillColor(sf::Color::Black);
    coinsText.setPosition(20, 20);
    coinsText.setString("Coins: " + std::to_string(userCoins));

    trolleyText.setFont(font);
    trolleyText.setCharacterSize(36);
    trolleyText.setFillColor(sf::Color::Black);
    trolleyText.setPosition(1700, 20);
    trolleyText.setString("Trolley: " + std::to_string(trolleyCount));

    insufficientFundsText.setFont(font);
    insufficientFundsText.setCharacterSize(36);
    insufficientFundsText.setFillColor(sf::Color::Red);
    insufficientFundsText.setPosition(800, 100);
    insufficientFundsText.setString("");

    // Load Trolley Image
    if (!trolleyTexture.loadFromFile("Images/Trolley.png")) {
        std::cerr << "Error: Trolley image not found at Images/Trolley.png" << std::endl;
        // Optionally, set a default texture or handle gracefully
    }
    trolleySprite.setTexture(trolleyTexture);
    trolleySprite.setPosition(1700, 70);
    trolleySprite.setScale(0.5f, 0.5f);
}

// Destructor
GenericShoppingWindow::~GenericShoppingWindow() {
    delete window;  // Clean up the window object
}

// Load items from the Shopping class
void GenericShoppingWindow::loadItems() {
    std::vector<std::string> itemNames = shoppingData.getItemNames();
    std::vector<std::string> imagePaths = shoppingData.getImagePaths();
    std::vector<int> itemPrices = shoppingData.getItemPrices();

    // Load each item and store in the items vector
    for (size_t i = 0; i < itemNames.size(); ++i) {
        Item item;
        item.name = itemNames[i];
        item.price = itemPrices[i];
        item.stock = 0; // Not used in Shopping Window

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

        // Initialize item description text
        sf::Text description;
        description.setFont(font);
        description.setCharacterSize(24);
        description.setFillColor(sf::Color::Black);
        description.setPosition(xPos, yPos + item.sprite.getGlobalBounds().height + 10);
        description.setString(item.name + " - " + std::to_string(item.price) + " coins");
        // Assuming you have a text member in Item, else manage separately

        items.push_back(item);
    }
}

// Open the shopping window
void GenericShoppingWindow::open() {
    window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Shopping Window");
    
    while (window->isOpen()) {
        handleEvents();
        render();
    }
}

// Handle user events (e.g., mouse clicks)
void GenericShoppingWindow::handleEvents() {
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

            // Check if any item was clicked
            for (auto& item : items) {
                if (item.sprite.getGlobalBounds().contains(static_cast<float>(x), static_cast<float>(y))) {
                    if (userCoins >= item.price) {
                        userCoins -= item.price;
                        basket.push_back(item);
                        trolleyCount++;

                        // Update UI texts
                        coinsText.setString("Coins: " + std::to_string(userCoins));
                        trolleyText.setString("Trolley: " + std::to_string(trolleyCount));

                        std::cout << "Purchased: " << item.name << std::endl;
                    }
                    else {
                        insufficientFundsText.setString("NOT ENOUGH GOLD");
                        std::cout << "Not enough coins to purchase: " << item.name << std::endl;
                    }
                }
            }
        }
    }
}

// Render the shopping window
void GenericShoppingWindow::render() {
    window->clear(sf::Color(245, 245, 220)); // Beige background

    // Draw UI Elements
    window->draw(coinsText);
    window->draw(trolleyText);
    window->draw(trolleySprite);

    // Draw Items and Descriptions
    for (const auto& item : items) {
        window->draw(item.sprite);
        // Assuming description text is managed separately or within Item
        // If you have description texts as part of Item, draw them here
    }

    // Draw Insufficient Funds Message
    window->draw(insufficientFundsText);

    window->display();
}
