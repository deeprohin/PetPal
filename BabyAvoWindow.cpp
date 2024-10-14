#include "BabyAvoWindow.h"
#include <filesystem>

// Constructor
BabyAvo::BabyAvo(sf::Font& font, int userCoins, std::vector<Item>& basket)
    : font(font), userCoins(userCoins), basket(basket), trolleyCount(0) {
    
    // Dynamically allocate the window
    window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Baby Avo Shop");

    // Print current working directory for debugging

    
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
    insufficientFundsText.setPosition(800, 100); // Position it below the trolley count
    insufficientFundsText.setString(""); // Initially empty

    // Load trolley image
    if (!trolleyTexture.loadFromFile("Images/Trolley.png")) {
        std::cerr << "Error: Trolley image not found at Images/Trolley.png" << std::endl;
        exit(1); // Exit program if texture fails to load
    }
    trolleySprite.setTexture(trolleyTexture);
    
    // Set trolley image position just below the trolley text
    trolleySprite.setPosition(1700, 70); // Adjust Y position as needed
    trolleySprite.setScale(0.5f, 0.5f); // Adjust scale as needed

    // Load shopping items
    loadItems();
}

// Destructor to clean up allocated memory
BabyAvo::~BabyAvo() {
    delete window; // Free the dynamically allocated memory for the window
}

void BabyAvo::loadItems() {
    const int numRows = 1; // Only one row for 4 images
    const int numCols = 4; // Four images in total
    const int itemWidth = 150;  // Desired item width
    const int itemHeight = 150; // Desired item height
    const int horizontalSpacing = 150; // Adjusted spacing for even distribution
    const int startY = 300; // Fixed Y position for the row of items

    // Calculate grid width and starting X position to center the items horizontally
    int gridWidth = numCols * itemWidth + (numCols - 1) * horizontalSpacing;
    int startX = (1920 - gridWidth) / 2-gridWidth/4; // Center the items horizontally

    // Item data (names, prices, image paths)
    std::vector<std::string> itemNames = {"Baby Pumpkin", "Baby Banana", "Yakult", "Baby Medicine"};
    std::vector<int> itemPrices = {100, 50, 50, 500};
    std::vector<std::string> imagePaths = {
        "Images/Pumpkin.png", 
        "Images/Banana.png", 
        "Images/Yakult.png", 
        "Images/BabyMedicine.png"
    };

    int index = 0;
    for (int col = 0; col < numCols; ++col) {
        if (index >= itemNames.size()) break;

        Item item;
        item.name = itemNames[index];
        item.price = itemPrices[index];

        // Create and load texture into shared_ptr
        item.texture = std::make_shared<sf::Texture>();
        if (!item.texture->loadFromFile(imagePaths[index])) {
            std::cerr << "Error: " << itemNames[index] << " image not found at " << imagePaths[index] << std::endl;
            index++;  // Skip this item and continue with the next
            continue;
        }

        // Set texture to sprite
        item.sprite.setTexture(*item.texture);

        // Scale the sprite to the desired size
        float scaleX = static_cast<float>(itemWidth) / item.texture->getSize().x;  // Calculate scale for width
        float scaleY = static_cast<float>(itemHeight) / item.texture->getSize().y; // Calculate scale for height
        item.sprite.setScale(scaleX, scaleY); // Set the scale

        // Calculate and set the sprite position
        int xPos = startX + col * (itemWidth + horizontalSpacing);
        item.sprite.setPosition(xPos, startY); // Fixed Y position

        std::cout << "Loaded " << item.name << " at position (" << xPos << ", " << startY << ")" << std::endl;

        // Add the item to the items list
        items.push_back(item);

        index++;
    }
}


// Open the shopping window and handle interactions
void BabyAvo::open() {
    while (window->isOpen()) {
        handleEvents();
        render();
    }
}

// Handle window events
void BabyAvo::handleEvents() {
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
void BabyAvo::render() {
    window->clear(sf::Color(230, 230, 220));  // Set background color to beige

    window->draw(coinsText);    // Display coins
    window->draw(trolleyText);  // Display trolley count
    window->draw(trolleySprite); // Draw the trolley image below the trolley count

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
