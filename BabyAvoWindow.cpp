#include "BabyAvoWindow.h"

#include <filesystem>

// Constructor
BabyAvo::BabyAvo(sf::Font& font, int userCoins, std::vector<Item>& basket)
    : font(font), userCoins(userCoins), basket(basket), trolleyCount(0) {
  // dynamically allocate the window
  window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Baby Avo Shop");

  // initalising coins text
  coinsText.setFont(font);
  coinsText.setCharacterSize(36);
  coinsText.setFillColor(sf::Color::Black);
  coinsText.setPosition(20, 20);
  coinsText.setString("Coins: " + std::to_string(userCoins));

  // intialising trolley count text
  trolleyText.setFont(font);
  trolleyText.setCharacterSize(36);
  trolleyText.setFillColor(sf::Color::Black);
  trolleyText.setPosition(1700, 20);
  trolleyText.setString("Trolley: " + std::to_string(trolleyCount));

  // intialising insufficient funds text
  insufficientFundsText.setFont(font);
  insufficientFundsText.setCharacterSize(36);
  insufficientFundsText.setFillColor(sf::Color::Red);
  insufficientFundsText.setPosition(800, 100);
  insufficientFundsText.setString("");  // initially empty

  // loading trolley image
  if (!trolleyTexture.loadFromFile("Images/Trolley.png")) {
    std::cout << "Error: Trolley image not found at Images/Trolley.png"
              << std::endl;
  }
  trolleySprite.setTexture(trolleyTexture);

  // setting trolley image position
  trolleySprite.setPosition(1700, 70);
  trolleySprite.setScale(0.5f, 0.5f);

  // loading shopping items
  loadItems();
}

// Destructor to clean up allocated memory
BabyAvo::~BabyAvo() { delete window; }
// function to load items
void BabyAvo::loadItems() {
  const int numRows = 1;
  const int numCols = 4;
  const int itemWidth = 150;          // desired item width
  const int itemHeight = 150;         // desired item height
  const int horizontalSpacing = 150;  // adjusted spacing for even distribution
  const int startY = 300;

  // calculating grid width and starting x position to center the items
  // horizontally
  int gridWidth = numCols * itemWidth + (numCols - 1) * horizontalSpacing;
  int startX = (1920 - gridWidth) / 2 -
               gridWidth / 4;  // centering the items horizontally

  // the data for items
  std::vector<std::string> itemNames = {"Baby Pumpkin", "Baby Banana", "Yakult",
                                        "Baby Medicine"};
  std::vector<int> itemPrices = {100, 50, 50, 500};
  std::vector<std::string> imagePaths = {
      "Images/Pumpkin.png", "Images/Banana.png", "Images/Yakult.png",
      "Images/BabyMedicine.png"};

  int index = 0;
  for (int col = 0; col < numCols; ++col) {
    if (index >= itemNames.size()) break;

    Item item;
    item.name = itemNames[index];
    item.price = itemPrices[index];

    // creating and loading texture into shared_ptr
    item.texture = std::make_shared<sf::Texture>();
    if (!item.texture->loadFromFile(imagePaths[index])) {
      std::cout << "Error: " << itemNames[index] << " image not found at "
                << imagePaths[index] << std::endl;
      index++;
      continue;
    }

    // setting texture to sprite
    item.sprite.setTexture(*item.texture);

    // scaling the sprite to the desired size
    float scaleX = static_cast<float>(itemWidth) /
                   item.texture->getSize().x;  // calculating scale for width
    float scaleY = static_cast<float>(itemHeight) /
                   item.texture->getSize().y;  // calculating scale for height
    item.sprite.setScale(scaleX, scaleY);      // setting the scale

    // calculating and set the sprite position
    int xPos = startX + col * (itemWidth + horizontalSpacing);
    item.sprite.setPosition(xPos, startY);  // fixed y position

    std::cout << "Loaded " << item.name << " at position (" << xPos << ", "
              << startY << ")" << std::endl;

    // adding the item to the items list
    items.push_back(item);

    index++;
  }
}

// opening the shopping window and handle interactions
void BabyAvo::open() {
  while (window->isOpen()) {
    handleEvents();
    render();
  }
}

// handling window events
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

      // resetting the insufficient funds message
      insufficientFundsText.setString("");

      // checking if any item was clicked
      for (auto& item : items) {
        sf::FloatRect bounds = item.sprite.getGlobalBounds();
        if (bounds.contains(static_cast<float>(x), static_cast<float>(y))) {
          if (userCoins >= item.price) {
            userCoins -= item.price;
            basket.push_back(item);
            trolleyCount++;  // incrementing trolley count
            std::cout << "Purchased: " << item.name << std::endl;

            // updating coins and trolley texts
            coinsText.setString("Coins: " + std::to_string(userCoins));
            trolleyText.setString("Trolley: " + std::to_string(trolleyCount));
          } else {
            std::cout << "Not enough coins to purchase: " << item.name
                      << std::endl;
            insufficientFundsText.setString("NOT ENOUGH GOLD");
          }
        }
      }
    }
  }
}

// rendering the shopping window
void BabyAvo::render() {
  window->clear(sf::Color(230, 230, 220));  // setting background color to beige

  window->draw(coinsText);    // displaying coins
  window->draw(trolleyText);  // displaying trolley count
  window->draw(
      trolleySprite);  // draw the trolley image below the trolley count

  // draw each item and display item name and price
  for (const auto& item : items) {
    window->draw(item.sprite);

    sf::Text itemText;
    itemText.setFont(font);
    itemText.setCharacterSize(24);
    itemText.setFillColor(sf::Color::Black);
    itemText.setPosition(item.sprite.getPosition().x,
                         item.sprite.getPosition().y +
                             item.sprite.getGlobalBounds().height + 10);
    itemText.setString(item.name + " - " + std::to_string(item.price) +
                       " coins");
    window->draw(itemText);
  }

  // draw the insufficient funds message if any
  window->draw(insufficientFundsText);

  window->display();
}
