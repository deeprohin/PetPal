#include "GenericEatingWindow.h"
#include <iostream>

GenericEatingWindow::GenericEatingWindow(sf::Font& font, std::vector<std::shared_ptr<BaseItem>>& eatingBasket, EatingShop& eatingShop)
    : font(font), basket(eatingBasket), EatingShopData(eatingShop) {
    // Initialize the SFML window
    window.create(sf::VideoMode(800, 600), "Eating Window");
}

void GenericEatingWindow::loadFoodItems() {
    // Get item names and image paths from EatingShop
    std::vector<std::string> itemNames = EatingShopData.getItemNames();
    std::vector<std::string> imagePaths = EatingShopData.getImagePaths();

    for (size_t i = 0; i < itemNames.size(); ++i) {
        // Create an Item object and initialize it
        Item item;
        item.name = itemNames[i];
        item.price = 10;  // Example price (can be updated based on your logic)
        item.stock = 1;   // Default stock

        // Load texture from the provided image path
        item.texture = std::make_shared<sf::Texture>();
        if (!item.texture->loadFromFile(imagePaths[i])) {
            std::cerr << "Error: Could not load image: " << imagePaths[i] << std::endl;
            continue;  // Skip if the texture fails to load
        }

        // Set sprite texture
        item.sprite.setTexture(*item.texture);

        // Wrap the Item in a shared pointer to BaseItem (polymorphism)
        std::shared_ptr<BaseItem> baseItemPtr = std::make_shared<Item>(item);

        // Add the shared_ptr<BaseItem> to the foodItems vector
        foodItems.push_back(baseItemPtr);
    }
}

void GenericEatingWindow::open() {
    loadFoodItems();

    // Main loop for the eating window
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handle other events like selecting an item, buying, etc.
        }

        window.clear(sf::Color::White); // Clear window with a white background

        // Render the food items on the window
        for (size_t i = 0; i < foodItems.size(); ++i) {
            auto& item = foodItems[i];

            // Draw the item's sprite
            window.draw(item->getSprite());

            // Optionally, draw item's price or other information
            // Example:
            sf::Text priceText;
            priceText.setFont(font);
            priceText.setString("$" + std::to_string(item->getPrice()));
            priceText.setPosition(100.f + i * 150.f, 500.f);  // Position example
            window.draw(priceText);
        }

        window.display();
    }
}
