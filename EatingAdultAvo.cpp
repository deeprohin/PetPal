#include "EatingAdultAvo.h"

// Constructor
EatingAdultAvo::EatingAdultAvo(sf::Font& font, Item* basket, int& basketSize, int& basketCapacity, int& trolleyCount)
    : font(font), basket(basket), basketSize(basketSize), basketCapacity(basketCapacity), trolleyCount(trolleyCount) {

    // Create a RenderWindow dynamically
    window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Eating Adult Avo");

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
EatingAdultAvo::~EatingAdultAvo() {
    delete window;  // Delete dynamically allocated window
}

// Load food items into the eating window
void EatingAdultAvo::loadFoodItems() {
    std::vector<std::string> itemNames = {"Steak", "Fried Rice", "Curry Chicken", "Boba", "Cold Rolls", "Medicine"};
    std::vector<int> itemPrices = {500, 200, 200, 150, 180, 500}; // Prices for the adult items (might not be needed)
    std::vector<std::string> imagePaths = {
        "Images/Steak.png",
        "Images/FriedRice.png",
        "Images/Curry.png",
        "Images/Boba.png",
        "Images/ColdRolls.png",
        "Images/Medicine.png"  // Ensure correct file extensions
    };

    // Define grid layout parameters
    const int columns = 3;
    const int rows = 2;
    const float horizontalSpacing = 300.0f; // Increased spacing to accommodate larger images
    const float verticalSpacing = 300.0f;   // Increased spacing to accommodate larger images
    const float startX = (1920 - (columns * 300.0f)) / 2.0f; // Center the grid horizontally
    const float startY = 150.0f; // Starting Y position

    // Load each food item
    for (size_t i = 0; i < itemNames.size(); ++i) {
        Item item;
        item.name = itemNames[i];
        item.price = itemPrices[i];
        item.stock = 5; // Initialize stock to 5 or any desired number

        // Load texture into shared_ptr
        item.texture = std::make_shared<sf::Texture>();
        if (!item.texture->loadFromFile(imagePaths[i])) {
            std::cerr << "Error: " << itemNames[i] << " image not found at " << imagePaths[i] << std::endl;
            exit(1);
        }

        // Set texture to sprite and scale it
        item.sprite.setTexture(*item.texture);
        item.sprite.setScale(0.5f, 0.5f); // Increased scale to enlarge images

        // Calculate grid position
        int row = i / columns;
        int col = i % columns;
        float xPosition = startX + col * horizontalSpacing;
        float yPosition = startY + row * verticalSpacing;
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
void EatingAdultAvo::open() {
    while (window->isOpen()) {
        handleEvents();
        render();
    }
}

// Handle window events
void EatingAdultAvo::handleEvents() {
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
                    auto it = std::find_if(basket, basket + basketSize, [&item](const Item& basketItem) {
                        return basketItem.name == item.name;
                    });

                    if (it != (basket + basketSize) && it->stock > 0) {
                        // Simulate eating the food item
                        it->stock--; // Decrease stock
                        trolleyCount++; // Increase trolley count
                        playEatingAnimation(item.name);
                        std::cout << "Ate: " << item.name << std::endl;

                        // Update the quantity display for this item
                        item.quantityText.setString("Quantity: " + std::to_string(it->stock));
                    } else {
                        insufficientFundsText.setString("NEED TO BUY MORE");
                    }
                }
            }
        }
    }
}

// Render the eating window
void EatingAdultAvo::render() {
    window->clear(sf::Color(245, 245, 220));  // Set background color to beige

    // Draw the fridge sprite
    window->draw(fridgeSprite);
    
    window->draw(insufficientFundsText); // Draw the insufficient funds message

    // Draw each food item and its quantity
    for (const auto& item : foodItems) {
        window->draw(item.sprite);
        window->draw(item.quantityText); // Display item quantity
    }

    window->display();
}

// Function to play eating animation
void EatingAdultAvo::playEatingAnimation(const std::string& foodName) {
    // Here, you could add animation logic, sound effects, or any feedback mechanism
    std::cout << "Eating animation for: " << foodName << std::endl;
    // Placeholder for animation logic
}

// Helper function to add an item to the basket
void EatingAdultAvo::addToBasket(const Item& item) {
    // Check if the basket is full
    if (basketSize >= basketCapacity) {
        // Double the capacity
        int newCapacity = basketCapacity * 2;
        Item* newBasket = new Item[newCapacity];

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
