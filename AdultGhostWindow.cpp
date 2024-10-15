#include "AdultGhostWindow.h"

#include <iostream>

// Constructor
AdultGhostWindow::AdultGhostWindow(sf::Font& font, int userCoins,
                                   std::vector<Item>& basket)
    : font(font), userCoins(userCoins), basket(basket), trolleyCount(0) {
  // Dynamically allocate the window
  window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Shopping");

  // Initializing coins text
  coinsText.setFont(font);
  coinsText.setCharacterSize(36);
  coinsText.setFillColor(sf::Color::Black);
  coinsText.setPosition(20, 20);
  coinsText.setString("Coins: " + std::to_string(userCoins));

  // Initializing trolley count text
  trolleyText.setFont(font);
  trolleyText.setCharacterSize(36);
  trolleyText.setFillColor(sf::Color::Black);
  trolleyText.setPosition(1700, 20);
  trolleyText.setString("Trolley: " + std::to_string(trolleyCount));

  // Initializing insufficient funds text
  insufficientFundsText.setFont(font);
  insufficientFundsText.setCharacterSize(36);
  insufficientFundsText.setFillColor(sf::Color::Red);
  insufficientFundsText.setPosition(800, 100);
  insufficientFundsText.setString("");  // Initially empty

  // Loading trolley image
  if (!trolleyTexture.loadFromFile("Images/Trolley.png")) {
    std::cerr << "Error: Trolley image not found at Images/Trolley.png"
              << std::endl;
  }
  trolleySprite.setTexture(trolleyTexture);

  // Setting trolley image position just below the trolley text
  trolleySprite.setPosition(1700, 70);
  trolleySprite.setScale(0.5f, 0.5f);

  // Loading shopping items
  loadItems();
}
// function to load items
void AdultGhostWindow::loadItems() {
  const int numRows = 2;
  const int numCols = 3;
  const int itemWidth = 150;
  const int itemHeight = 150;
  const int horizontalSpacing = 200;
  const int verticalSpacing = 250;

  // calculations to center the items on the window
  int gridWidth = (itemWidth + horizontalSpacing) * numCols - horizontalSpacing;
  int gridHeight = (itemHeight + verticalSpacing) * numRows - verticalSpacing;
  int startX = (1920 - gridWidth) / 2 - gridWidth / 4;
  int startY = (1080 - gridHeight) / 2 - gridHeight / 4;

  // Loading each item with individual textures and set position
  std::vector<std::string> itemNames = {"Chicken",  "Milk",  "Apple",
                                        "Medicine", "Pizza", "Fish"};
  std::vector<int> itemPrices = {100, 50, 50, 500, 70, 70};
  std::vector<std::string> imagePaths = {
      "Images/Chicken.png",  "Images/Milk.png",  "Images/Apple.png",
      "Images/Medicine.png", "Images/Pizza.png", "Images/Fish.png"};

  int index = 0;
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      if (index >= itemNames.size()) break;

      Item item;
      item.name = itemNames[index];
      item.price = itemPrices[index];

      // creating and load texture into shared_ptr
      item.texture = std::make_shared<sf::Texture>();
      if (!item.texture->loadFromFile(imagePaths[index])) {
        std::cerr << "Error: " << itemNames[index] << " image not found at "
                  << imagePaths[index] << std::endl;
      }

      // setting texture to sprite
      item.sprite.setTexture(*item.texture);

      // scaling the sprite to the desired size
      float scaleX = static_cast<float>(itemWidth) / item.texture->getSize().x;
      float scaleY = static_cast<float>(itemHeight) / item.texture->getSize().y;
      item.sprite.setScale(scaleX, scaleY);  // setting the scale

      // calculating and setting the sprite position
      int xPos = startX + col * (itemWidth + horizontalSpacing);
      int yPos = startY + row * (itemHeight + verticalSpacing);
      item.sprite.setPosition(xPos, yPos);

      std::cout << "Loaded " << item.name << " at position (" << xPos << ", "
                << yPos << ")" << std::endl;

      // adding hte items to the vector
      items.push_back(item);

      index++;
    }
  }
}

// function to opent he window
void AdultGhostWindow::open() {
  while (window->isOpen()) {
    handleEvents();
    render();
  }
}

// handling events based on the interactions
void AdultGhostWindow::handleEvents() {
  sf::Event event;
  while (window->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window->close();
    }
    // for when the mouse button is pressed
    if (event.type == sf::Event::MouseButtonPressed) {
      sf::Vector2i clickPos = sf::Mouse::getPosition(*window);
      int x = clickPos.x;
      int y = clickPos.y;

      // resetting the insufficient funds message
      insufficientFundsText.setString("");

      // checkking if any item has been clicked
      for (auto& item : items) {
        sf::FloatRect bounds = item.sprite.getGlobalBounds();
        if (bounds.contains(static_cast<float>(x), static_cast<float>(y))) {
          if (userCoins >= item.price) {
            userCoins -= item.price;
            basket.push_back(item);
            trolleyCount++;  // increasing the trolley count
            std::cout << "Purchased: " << item.name << std::endl;

            // updaitng hte coinds
            coinsText.setString("Coins: " + std::to_string(userCoins));
            trolleyText.setString("Trolley: " + std::to_string(trolleyCount));
          } else {
            std::cout << "Not enough coins to purchase: " << item.name
                      << std::endl;
            insufficientFundsText.setString("NOT ENOUGH COINS");
          }
        }
      }
    }
  }
}

// rendering the shopping window
void AdultGhostWindow::render() {
  window->clear(sf::Color(230, 230, 220));  /// background color stting

  window->draw(coinsText);  // disaplying coins and other stuff
  window->draw(trolleyText);
  window->draw(
      trolleySprite);  // drawing the trolley image below the trolley count

  // drawing each item and display item name and price
  for (const auto& item : items) {
    window->draw(item.sprite);

    sf::Text itemText;
    itemText.setFont(font);
    itemText.setCharacterSize(34);
    itemText.setFillColor(sf::Color::Black);
    itemText.setPosition(item.sprite.getPosition().x,
                         item.sprite.getPosition().y +
                             item.sprite.getGlobalBounds().height + 10);
    itemText.setString(item.name + " - " + std::to_string(item.price) +
                       " coins");
    window->draw(itemText);
  }

  // Draw the insufficient funds message if any
  window->draw(insufficientFundsText);

  window->display();
}
// destructor
AdultGhostWindow::~AdultGhostWindow() { delete window; }