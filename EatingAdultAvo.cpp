#include "EatingAdultAvo.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include "pet_stats.h"

// constructor
EatingAdultAvo::EatingAdultAvo(sf::Font& font, ItemList* basket,
                               int& basketSize, int& basketCapacity,
                               int& trolleyCount)
    : font(font),
      basket(basket),
      basketSize(basketSize),
      basketCapacity(basketCapacity),
      trolleyCount(trolleyCount) {
  // create a RenderWindow dynamically
  window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Eating Adult Avo");

  // loading fridge background image
  if (!fridgeTexture.loadFromFile("Images/Fridge.png")) {
    std::cerr << "Error: Fridge image not found!" << std::endl;
    exit(1);
  }
  fridgeSprite.setTexture(fridgeTexture);
  fridgeSprite.setScale(static_cast<float>(1920) /
                            fridgeTexture.getSize().x,  // Scale to fit width
                        static_cast<float>(1080) /
                            fridgeTexture.getSize().y  // Scale to fit height
  );
  fridgeSprite.setPosition(0, 0);  // Set position to cover the window

  // Initialize insufficient funds text
  insufficientFundsText.setFont(font);
  insufficientFundsText.setCharacterSize(36);
  insufficientFundsText.setFillColor(sf::Color::Red);
  insufficientFundsText.setPosition(800, 100);
  insufficientFundsText.setString("");  // Initially empty

  // Load food items
  loadFoodItems();
}

// Destructor to clean up dynamic memory
EatingAdultAvo::~EatingAdultAvo() {
  delete window;  // Delete dynamically allocated window
}

void EatingAdultAvo::loadFoodItems() {
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
  const int columns = 3;                  // 3 columns
  const int rows = 3;                     // 3 rows (for a 3x3 grid)
  const float itemSize = 150.0f;          // Fixed size for each item (150x150)
  const float horizontalSpacing = 50.0f;  // Spacing between images
  const float verticalSpacing = 50.0f;    // Spacing between images
  const float startX =
      (1920 - (columns * itemSize + (columns - 1) * horizontalSpacing)) /
      2.0f;  // Center grid horizontally
  const float startY =
      (1080 - (rows * itemSize + (rows - 1) * verticalSpacing)) /
      2.0f;  // Center grid vertically

    // Load each food item
    for (size_t i = 0; i < itemNames.size(); ++i) {
        ItemList item;
        item.name = itemNames[i];
        item.price = itemPrices[i];
        item.stock = stockData.count(itemNames[i]) ? stockData[itemNames[i]] : 0;; // Initialize stock to 5 or any desired number

    // Load texture into shared_ptr
    item.texture = std::make_shared<sf::Texture>();
    if (!item.texture->loadFromFile(imagePaths[i])) {
      std::cerr << "Error: " << itemNames[i] << " image not found at "
                << imagePaths[i] << std::endl;
      exit(1);
    }

    // Set texture to sprite and scale it
    item.sprite.setTexture(*item.texture);
    item.sprite.setScale(
        itemSize / item.texture->getSize().x,
        itemSize / item.texture->getSize().y);  // Scale to fixed size

    // Calculate grid position
    int row = i / columns;  // Determine row index
    int col = i % columns;  // Determine column index
    float xPosition =
        startX + col * (itemSize + horizontalSpacing);  // Calculate x position
    float yPosition =
        startY + row * (itemSize + verticalSpacing);  // Calculate y position
    item.sprite.setPosition(xPosition, yPosition);    // Set sprite position

    // Initialize quantity text for each item
    item.quantityText.setFont(font);
    item.quantityText.setCharacterSize(28);  // Slightly larger font size
    item.quantityText.setFillColor(sf::Color::Black);
    // Position the text below the sprite
    item.quantityText.setPosition(
        xPosition,
        yPosition + item.sprite.getGlobalBounds().height +
            15  // Position text below the image
    );
    item.quantityText.setString("Quantity: " + std::to_string(item.stock));

    foodItems.push_back(item);  // Add the item to the food items vector
  }
}

// Open the eating window and handle interactions
void EatingAdultAvo::open(PetStats& petStats) {
  while (window->isOpen()) {
    handleEvents(petStats);
    render();
  }
}

// Handle window events
void EatingAdultAvo::handleEvents(PetStats& petStats) {
  sf::Event event;
  while (window->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window->close();
    }
    // Check for the Esc key press to close the window
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Escape) {
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
          auto it = std::find_if(basket, basket + basketSize,
                                 [&item](const ItemList& basketItem) {
                                   return basketItem.name == item.name;
                                 });

          if (it != (basket + basketSize) && it->stock > 0) {
            // Simulate eating the food item
            it->stock--;     // Decrease stock
            trolleyCount++;  // Increase trolley count
            playEatingAnimation(item.name);
            std::cout << "Ate: " << item.name << std::endl;

            // Update the quantity display for this item
            item.quantityText.setString("Quantity: " +
                                        std::to_string(it->stock));
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

  window->draw(insufficientFundsText);  // Draw the insufficient funds message

  // Draw each food item and its quantity
  for (const auto& item : foodItems) {
    window->draw(item.sprite);
    window->draw(item.quantityText);  // Display item quantity
  }

  window->display();
}

// Function to play eating animation
void EatingAdultAvo::playEatingAnimation(const std::string& foodName) {
  // Here, you could add animation logic, sound effects, or any feedback
  // mechanism
  std::cout << "Eating animation for: " << foodName << std::endl;
  // Placeholder for animation logic
}

// Helper function to add an item to the basket
void EatingAdultAvo::addToBasket(const ItemList& item) {
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