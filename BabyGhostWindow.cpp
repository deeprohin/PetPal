#include "BabyGhostWindow.h"
#include <iostream>

// Constructor
BabyGhostShoppingWindow::BabyGhostShoppingWindow(sf::Font& font, int userCoins, std::vector<Item>& basket)
    : font(font), userCoins(userCoins), basket(basket), trolleyCount(0) {

    // Dynamically allocate the RenderWindow
    window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Baby Ghost Shopping");

    // Initialize coins text
    coinsText.setFont(font);
    coinsText.setCharacterSize(36);
    coinsText.setFillColor(sf::Color::Black);
    coinsText.setPosition(20, 20);
    coinsText.setString("Coins: " + std::to_string(userCoins));

    // Initialize trolley count text
    trolleyText.setFont(font);
    trolleyText.setCharacterSize(36);
    trolleyText.setFillColor(sf::Color::Black);
    trolleyText.setPosition(1700, 20);
    trolleyText.setString("Trolley: " + std::to_string(trolleyCount));

    // Initialize insufficient funds text
    insufficientFundsText.setFont(font);
    insufficientFundsText.setCharacterSize(36);
    insufficientFundsText.setFillColor(sf::Color::Red);
    insufficientFundsText.setPosition(800, 100);
    insufficientFundsText.setString(""); // Initially empty

    // Load trolley image
    if (!trolleyTexture.loadFromFile("Images/Trolley.png")) {
        std::cerr << "Error: Baby trolley image not found at Images/Trolley.png" << std::endl;
        exit(1); // Exit program if texture fails to load
    }
    trolleySprite.setTexture(trolleyTexture);
    trolleySprite.setPosition(1700, 70); // Adjust position as needed
    trolleySprite.setScale(0.5f, 0.5f); // Scale the trolley sprite

    // Load shopping items
    loadItems();
}

// Destructor to clean up dynamically allocated memory
BabyGhostShoppingWindow::~BabyGhostShoppingWindow() {
        delete window;

}

void BabyGhostShoppingWindow::loadItems() {
    const int numRows = 2; // Set to 2 rows for four items
    const int numCols = 2; // Set to 2 columns for four items
    const int itemWidth = 150;
    const int itemHeight = 150;
    const int horizontalSpacing = 200;
    const int verticalSpacing = 250;

    // Calculate offsets to center the grid in the window
    int gridWidth = (itemWidth + horizontalSpacing) * numCols - horizontalSpacing;
    int gridHeight = (itemHeight + verticalSpacing) * numRows - verticalSpacing;
    int startX = (1920 - gridWidth) / 2-gridWidth/4;
    int startY = (1080 - gridHeight) / 2-gridHeight/4;

    // Load each item with individual textures and set position
    std::vector<std::string> itemNames = {"Baby Milk", "Baby Porridge", "Yoghurt", "Baby Medicine"};
    std::vector<int> itemPrices = {50, 30, 70, 500}; // Update prices to include all four items
    std::vector<std::string> imagePaths = {
        "Images/Milk2.png", 
        "Images/Porridge.png", 
        "Images/Yoghurt.png", 
        "Images/BabyMedicine.png"  // Ensure correct file extensions
    };

    int index = 0;
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            if (index >= itemNames.size()) break;

            Item item;
            item.name = itemNames[index];
            item.price = itemPrices[index];
            
            // Create and load texture into shared_ptr
            item.texture = std::make_shared<sf::Texture>();
            if (!item.texture->loadFromFile(imagePaths[index])) {
                std::cerr << "Error: " << itemNames[index] << " image not found at " << imagePaths[index] << std::endl;
            }

            // Set texture to sprite
            item.sprite.setTexture(*item.texture);
            
            // Calculate and set the sprite position
            int xPos = startX + col * (itemWidth + horizontalSpacing);
            int yPos = startY + row * (itemHeight + verticalSpacing); // Position for multiple rows
            item.sprite.setPosition(xPos, yPos);
            
            std::cout << "Loaded " << item.name << " at position (" << xPos << ", " << yPos << ")" << std::endl;

            // Add the item to the items list
            items.push_back(item);
            index++;
        }
    }
}

// Open the shopping window and handle interactions
void BabyGhostShoppingWindow::open() {
    if (!window) return; // Ensure window is valid

    while (window->isOpen()) {
        handleEvents();
        render();
    }
}

// Handle window events
void BabyGhostShoppingWindow::handleEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {  // Use -> for pointer access
        if (event.type == sf::Event::Closed) {
            window->close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i clickPos = sf::Mouse::getPosition(*window); // Dereference window pointer
            int x = clickPos.x;
            int y = clickPos.y;

            // Reset the insufficient funds message
            insufficientFundsText.setString("");

            // Check if any item was clicked
            for (auto& item : items) {
                sf::FloatRect bounds = item.sprite.getGlobalBounds();
                if (bounds.contains(static_cast<float>(x), static_cast<float>(y))) {
                    if (userCoins >= item.price) {
                        userCoins -= item.price;
                        item.stock++;
                        basket.push_back(item);
                        trolleyCount++;  // Increment trolley count
                        std::cout << "Purchased: " << item.name << std::endl;

                        // Update coins and trolley texts
                        coinsText.setString("Coins: " + std::to_string(userCoins));
                        trolleyText.setString("Trolley: " + std::to_string(trolleyCount));
                    } else {
                        std::cout << "Not enough coins to purchase: " << item.name << std::endl;
                        insufficientFundsText.setString("NOT ENOUGH GOLD");
                    }
                }
            }
        }
    }
}

// Render the shopping window
void BabyGhostShoppingWindow::render() {
    window->clear(sf::Color(230, 230, 220));  // Set background color to beige

    window->draw(coinsText);    // Display coins
    window->draw(trolleyText);  // Display trolley count
    window->draw(trolleySprite); // Render the trolley sprite

    // Draw each item and display item name and price
    for (const auto& item : items) {
        window->draw(item.sprite);

        sf::Text itemText;
        itemText.setFont(font);
        itemText.setCharacterSize(24);
        itemText.setFillColor(sf::Color::Black);
        itemText.setPosition(item.sprite.getPosition().x, item.sprite.getPosition().y + item.sprite.getGlobalBounds().height + 10);
        itemText.setString(item.name + " - " + std::to_string(item.price) + " coins");
        window->draw(itemText);
    }

    // Draw the insufficient funds message if any
    window->draw(insufficientFundsText);

    window->display();
}
