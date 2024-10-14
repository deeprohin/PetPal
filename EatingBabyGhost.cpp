#include "EatingBabyGhost.h"

// Constructor
EatingBabyGhost::EatingBabyGhost(sf::Font& font, ItemList* basket, int& basketSize, int& basketCapacity, int& trolleyCount)
    : font(font), basket(basket), basketSize(basketSize), basketCapacity(basketCapacity), trolleyCount(trolleyCount) {

    // Dynamically create a RenderWindow
    window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Eating Baby Ghost");

    // Load fridge background image
    if (!fridgeTexture.loadFromFile("Images/Fridge.png")) {
        std::cerr << "Error: Fridge image not found!" << std::endl;
        exit(1);
    }
    fridgeSprite.setTexture(fridgeTexture);
    fridgeSprite.setScale(
        static_cast<float>(1920) / fridgeTexture.getSize().x,
        static_cast<float>(1080) / fridgeTexture.getSize().y
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
EatingBabyGhost::~EatingBabyGhost() {
    // Clean up the dynamically allocated window
    delete window;
}

void EatingBabyGhost::loadFoodItems() {
    std::vector<std::string> itemNames = {"Baby Milk", "Baby Porridge", "Yoghurt", "Baby Medicine"};
    std::vector<int> itemPrices = {50, 30, 70, 500}; // Update prices to include all four items
    std::vector<std::string> imagePaths = {
        "Images/Milk2.png", 
        "Images/Porridge.png", 
        "Images/Yoghurt.png", 
        "Images/BabyMedicine.png"  // Ensure correct file extensions
    };
    

    // Define grid layout parameters
    const int columns = 2; // Adjust columns as needed
    const int rows = 2;    // Adjust rows as needed
    const float horizontalSpacing = 300.0f; 
    const float verticalSpacing = 300.0f;   
    const float startX = (1920 - (columns * horizontalSpacing)) / 2.0f; // Center the grid horizontally
    const float startY = 150.0f; // Starting Y position

    const int maxSize = 150;  // Maximum size for width and height

    // Load each food item
    for (size_t i = 0; i < itemNames.size(); ++i) {
        ItemList item;
        item.name = itemNames[i];
        item.price = itemPrices[i];
        item.stock = 5; // Initialize stock to 5

        // Load texture into shared_ptr
        item.texture = std::make_shared<sf::Texture>();
        if (!item.texture->loadFromFile(imagePaths[i])) {
            std::cerr << "Error: " << itemNames[i] << " image not found at " << imagePaths[i] << std::endl;
            exit(1);
        }

        // Set texture to sprite
        item.sprite.setTexture(*item.texture);

        // Get the original size of the image
        sf::Vector2u textureSize = item.texture->getSize();
        float width = textureSize.x;
        float height = textureSize.y;

        // Calculate the scaling factor based on the larger dimension (width or height)
        float scaleFactor = static_cast<float>(maxSize) / std::max(width, height);

        // Apply the same scale to both dimensions to maintain the aspect ratio
        item.sprite.setScale(scaleFactor, scaleFactor);

        // Calculate grid position
        int row = i / columns;
        int col = i % columns;
        float xPosition = startX + col * horizontalSpacing;
        float yPosition = startY + row * verticalSpacing;
        item.sprite.setPosition(xPosition, yPosition);

        // Initialize quantity text for each item
        item.quantityText.setFont(font);
        item.quantityText.setCharacterSize(28); 
        item.quantityText.setFillColor(sf::Color::Black);
        item.quantityText.setPosition(
            xPosition,
            yPosition + item.sprite.getGlobalBounds().height + 15
        );

        item.quantityText.setString("Quantity: " + std::to_string(item.stock));

        // Add the item to the list of food items
        foodItems.push_back(item);
    }
}


// Open the eating window and handle interactions
void EatingBabyGhost::open() {
    while (window->isOpen()) {
        handleEvents();
        render();
    }
}

// Handle window events
void EatingBabyGhost::handleEvents() {
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
                    auto it = std::find_if(basket, basket + basketSize, [&item](const ItemList& basketItem) {
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
void EatingBabyGhost::render() {
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
void EatingBabyGhost::playEatingAnimation(const std::string& foodName) {
    // Here, you could add animation logic, sound effects, or any feedback mechanism
    std::cout << "Eating animation for: " << foodName << std::endl;
    // Placeholder for animation logic
}
