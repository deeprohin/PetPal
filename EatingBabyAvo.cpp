#include "EatingBabyAvo.h"

// Constructor
EatingBabyAvo::EatingBabyAvo(sf::Font& font, ItemList* basket, int& basketSize, int& basketCapacity, int& trolleyCount)
    : font(font), basket(basket), basketSize(basketSize), basketCapacity(basketCapacity), trolleyCount(trolleyCount) {

    // Dynamically create a RenderWindow
    window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Eating Baby Avo");

    // Load background image
    if (!backgroundTexture.loadFromFile("Images/Fridge.png")) {
        std::cerr << "Error: Background image not found!" << std::endl;
        exit(1);
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(1920) / backgroundTexture.getSize().x, // Scale to fit width
        static_cast<float>(1080) / backgroundTexture.getSize().y  // Scale to fit height
    );
    backgroundSprite.setPosition(0, 0); // Set position to cover the window

    // Initialize insufficient funds text
    insufficientFundsText.setFont(font);
    insufficientFundsText.setCharacterSize(36);
    insufficientFundsText.setFillColor(sf::Color::Red);
    insufficientFundsText.setPosition(800, 100);
    insufficientFundsText.setString(""); // Initially empty

    // Load food items
    loadFoodItems();
}

// Destructor
EatingBabyAvo::~EatingBabyAvo() {
    // Clean up the dynamically allocated window
    delete window;
}

// Load food items into the eating window
void EatingBabyAvo::loadFoodItems() {
    std::vector<std::string> itemNames = {"Baby Pumpkin", "Baby Banana", "Yakult", "Baby Medicine"};
    std::vector<int> itemPrices = {100, 50, 50, 500}; // Prices for the baby items
    std::vector<std::string> imagePaths = {
        "Images/Pumpkin.png",
        "Images/Banana.png",
        "Images/Yakult.png",
        "Images/BabyMedicine.png" // Ensure correct file extensions
    };

    // Define grid layout parameters
    const int columns = 2;          // 2 columns for the grid
    const int rows = 2;             // 2 rows for the grid
    const float itemWidth = 150.0f; // Desired width for each item
    const float itemHeight = 150.0f;// Desired height for each item
    const float horizontalSpacing = 300.0f; // Spacing between columns
    const float verticalSpacing = 300.0f;   // Spacing between rows
    const float startX = (1920 - (columns * (itemWidth + horizontalSpacing))) / 2.0f; // Center the grid horizontally
    const float startY = 150.0f; // Starting Y position

    // Load each food item
    for (size_t i = 0; i < itemNames.size(); ++i) {
        ItemList item;
        item.name = itemNames[i];
        item.price = itemPrices[i];
        item.stock = 5; // Initialize stock to 5 or any desired number

        // Load texture into shared_ptr
        item.texture = std::make_shared<sf::Texture>();
        if (!item.texture->loadFromFile(imagePaths[i])) {
            std::cerr << "Error: " << itemNames[i] << " image not found at " << imagePaths[i] << std::endl;
            exit(1);
        }

        // Set texture to sprite
        item.sprite.setTexture(*item.texture);

        // Scale the sprite to the desired size (150x150)
        sf::Vector2u textureSize = item.texture->getSize();
        float scaleX = itemWidth / textureSize.x;
        float scaleY = itemHeight / textureSize.y;
        item.sprite.setScale(scaleX, scaleY); // Scale uniformly to 150x150

        // Calculate grid position
        int row = i / columns;
        int col = i % columns;
        float xPosition = startX + col * (itemWidth + horizontalSpacing);
        float yPosition = startY + row * (itemHeight + verticalSpacing);
        item.sprite.setPosition(xPosition, yPosition);

        // Initialize quantity text for each item
        item.quantityText.setFont(font);
        item.quantityText.setCharacterSize(28); // Slightly larger font size
        item.quantityText.setFillColor(sf::Color::Black);
        // Position the text below the sprite
        item.quantityText.setPosition(
            xPosition,
            yPosition + item.sprite.getGlobalBounds().height + 15 // Increased spacing below the image
        );
        item.quantityText.setString("Quantity: " + std::to_string(item.stock));

        foodItems.push_back(item);
    }
}


// Open the eating window and handle interactions
void EatingBabyAvo::open() {
    while (window->isOpen()) {
        handleEvents();
        render();
    }
}

void EatingBabyAvo::handleEvents() {
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
                    // Check stock from foodItems
                    if (item.stock > 0) {
                        // Simulate eating the food item
                        item.stock--; // Decrease stock in foodItems
                        trolleyCount++; // Increase trolley count
                        playEatingAnimation(item.name);
                        std::cout << "Ate: " << item.name << std::endl;

                        // Update the quantity display for this item
                        item.quantityText.setString("Quantity: " + std::to_string(item.stock));

                        // Now, find the item in the basket or add it if not present
                        auto it = std::find_if(basket, basket + basketSize, [&item](const ItemList& basketItem) {
                            return basketItem.name == item.name;
                        });

                        if (it != (basket + basketSize)) {
                            // Update the basket item stock if it exists
                            it->stock--; // Decrease stock in the basket
                        } else {
                            // If the item is not in the basket, add it
                            addToBasket(item);
                        }
                    } else {
                        // If item stock is 0, display the insufficient message
                        insufficientFundsText.setString("NEED TO BUY MORE");
                    }
                }
            }
        }
    }
}


// Render the eating window
void EatingBabyAvo::render() {
    window->clear(sf::Color(245, 245, 220));  // Set background color to beige

    // Draw the background sprite
    window->draw(backgroundSprite);
    
    window->draw(insufficientFundsText); // Draw the insufficient funds message

    // Draw each food item and its quantity
    for (const auto& item : foodItems) {
        window->draw(item.sprite);
        window->draw(item.quantityText); // Display item quantity
    }

    window->display();
}

// Function to play eating animation
void EatingBabyAvo::playEatingAnimation(const std::string& foodName) {
    // Here, you could add animation logic, sound effects, or any feedback mechanism
    std::cout << "Eating animation for: " << foodName << std::endl;
}

// Helper function to add an item to the basket
void EatingBabyAvo::addToBasket(const ItemList& item) {
    // Check if the basket is full
    if (basketSize >= basketCapacity) {
        // Double the capacity
        int newCapacity = basketCapacity * 2;
        ItemList* newBasket = new ItemList[newCapacity];

        // Copy existing items to the new basket
        for (int i = 0; i < basketSize; ++i) {
            newBasket[i] = basket[i];
        }

        // Delete the old basket
        delete[] basket;

        // Update basket pointers and capacity
        basket = newBasket;
        basketCapacity = newCapacity;

        std::cout << "Basket capacity increased to " << basketCapacity << std::endl;
    }

    // Add the new item to the basket
    basket[basketSize] = item;
    basketSize++;
}