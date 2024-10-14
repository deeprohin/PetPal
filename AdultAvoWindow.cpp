
#include "AdultAvoWindow.h"
#include <iostream>
int defaultCoins = 0;
std::vector<Item> defaultBasket;
// Constants for window dimensions and positions
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
const int ITEM_SIZE = 150;  // Set a uniform size for item sprites
const int HORIZONTAL_SPACING = 200;
const int VERTICAL_SPACING = 250;
const int FONT_SIZE_COINS = 36;
const int FONT_SIZE_ITEM = 24;
const sf::Color BACKGROUND_COLOR(230, 230, 220);
const sf::Color COINS_TEXT_COLOR = sf::Color::Black;
const sf::Color TROLLEY_TEXT_COLOR = sf::Color::Black;
const sf::Color INSUFFICIENT_FUNDS_COLOR = sf::Color::Red;

// Constructor
AdultAvoShoppingWindow::AdultAvoShoppingWindow(sf::Font& font, int userCoins, std::vector<Item>& basket)
    : font(font), userCoins(userCoins), basket(basket), trolleyCount(0) {
        
    // Dynamically allocate the window
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Adult Avo Shopping");

    // Initialize coins text
    coinsText.setFont(font);
    coinsText.setCharacterSize(FONT_SIZE_COINS);
    coinsText.setFillColor(COINS_TEXT_COLOR);
    coinsText.setPosition(20, 20);
    coinsText.setString("Coins: " + std::to_string(userCoins));

    // Initialize trolley count text
    trolleyText.setFont(font);
    trolleyText.setCharacterSize(FONT_SIZE_COINS);
    trolleyText.setFillColor(TROLLEY_TEXT_COLOR);
    trolleyText.setPosition(1700, 20);
    trolleyText.setString("Trolley: " + std::to_string(trolleyCount));

    // Initialize insufficient funds text
    insufficientFundsText.setFont(font);
    insufficientFundsText.setCharacterSize(FONT_SIZE_COINS);
    insufficientFundsText.setFillColor(INSUFFICIENT_FUNDS_COLOR);
    insufficientFundsText.setPosition(800, 100); // Position it below the trolley count
    insufficientFundsText.setString(""); // Initially empty

    // Load trolley image
    if (!trolleyTexture.loadFromFile("Images/Trolley.png")) {
        std::cerr << "Error: Adult trolley image not found at Images/Trolley.png" << std::endl;
    }
    trolleySprite.setTexture(trolleyTexture);
    trolleySprite.setPosition(1700, 70); // Adjust Y position as needed
    trolleySprite.setScale(0.5f, 0.5f); // Scale the trolley sprite

    // Load shopping items
    loadItems();
}

// Destructor to clean up allocated memory
AdultAvoShoppingWindow::~AdultAvoShoppingWindow() {
    delete window; // Free the dynamically allocated memory for the window
}

void AdultAvoShoppingWindow::loadItems() {
    const int numRows = 2; // Set to 2 rows for multiple items
    const int numCols = 3; // Columns for item layout

    // Load each item with individual textures and set position
    std::vector<std::string> itemNames = {"Steak", "Fried Rice", "Curry Chicken", "Boba", "Cold Rolls", "Medicine"};
    std::vector<int> itemPrices = {500, 200, 200, 150, 180, 500}; // Prices for the adult items
    std::vector<std::string> imagePaths = {
        "Images/Steak.png",
        "Images/FriedRice.png",
        "Images/Curry.png",
        "Images/Boba.png",
        "Images/ColdRolls.png",
        "Images/Medicine.png"  // Ensure correct file extensions
    };

    for (int index = 0; index < itemNames.size(); ++index) {
        Item item;
        item.name = itemNames[index];
        item.price = itemPrices[index];

        // Create and load texture into shared_ptr
        item.texture = std::make_shared<sf::Texture>();
        if (!item.texture->loadFromFile(imagePaths[index])) {
            std::cerr << "Error: " << itemNames[index] << " image not found at " << imagePaths[index] << std::endl;
           // Exit program if texture fails to load
        }

        // Set texture to sprite
        item.sprite.setTexture(*item.texture);

        // Calculate and set the sprite position
        int col = index % numCols;
        int row = index / numCols;
        int xPos = (WINDOW_WIDTH - (ITEM_SIZE * numCols + HORIZONTAL_SPACING * (numCols - 1))) / 2 + col * (ITEM_SIZE + HORIZONTAL_SPACING);
        int yPos = (WINDOW_HEIGHT - (ITEM_SIZE * numRows + VERTICAL_SPACING * (numRows - 1))) / 2 + row * (ITEM_SIZE + VERTICAL_SPACING);
        item.sprite.setPosition(xPos, yPos);
        
        // Scale item sprite to uniform size
        item.sprite.setScale(static_cast<float>(ITEM_SIZE) / item.sprite.getGlobalBounds().width, static_cast<float>(ITEM_SIZE) / item.sprite.getGlobalBounds().height);

        std::cout << "Loaded " << item.name << " at position (" << xPos << ", " << yPos << ")" << std::endl;

        // Add the item to the items list
        items.push_back(item);
    }
}

// Open the shopping window and handle interactions
void AdultAvoShoppingWindow::open() {
    while (window->isOpen()) {
        handleEvents();
        render();
    }
}

// Handle window events
void AdultAvoShoppingWindow::handleEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i clickPos = sf::Mouse::getPosition(*window);
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
void AdultAvoShoppingWindow::render() {
    window->clear(BACKGROUND_COLOR);  // Set background color

    window->draw(coinsText);    // Display coins
    window->draw(trolleyText);  // Display trolley count

    // Draw the trolley image
    window->draw(trolleySprite); // Render the trolley sprite

    // Draw each item and display item name and price
    for (const auto& item : items) {
        window->draw(item.sprite);

        sf::Text itemText;
        itemText.setFont(font);
        itemText.setCharacterSize(FONT_SIZE_ITEM);
        itemText.setFillColor(sf::Color::Black);
        itemText.setPosition(item.sprite.getPosition().x, item.sprite.getPosition().y + item.sprite.getGlobalBounds().height + 10);
        itemText.setString(item.name + " - " + std::to_string(item.price) + " coins");
        window->draw(itemText);
    }

    // Draw the insufficient funds message if any
    window->draw(insufficientFundsText);

    window->display();
}
