#include "AdultAvoWindow.h"

#include <iostream>
// setting the default coins to zero and setting up a default basket
int defaultCoins = 0;
std::vector<Item> defaultBasket;
// specifying constants for window dimensions and positions
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

// constructor for AdultAvoShoppingWindow
AdultAvoShoppingWindow::AdultAvoShoppingWindow(sf::Font& font, int userCoins,
                                               std::vector<Item>& basket)
    : font(font), userCoins(userCoins), basket(basket), trolleyCount(0) {
  // dynamically allocating the window
  window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                                "Adult Avo Shopping");

  // initializing coins text
  coinsText.setFont(font);
  coinsText.setCharacterSize(FONT_SIZE_COINS);
  coinsText.setFillColor(COINS_TEXT_COLOR);
  coinsText.setPosition(20, 20);
  coinsText.setString("Coins: " + std::to_string(userCoins));

  // initializing trolley count text
  trolleyText.setFont(font);
  trolleyText.setCharacterSize(FONT_SIZE_COINS);
  trolleyText.setFillColor(TROLLEY_TEXT_COLOR);
  trolleyText.setPosition(1700, 20);
  trolleyText.setString("Trolley: " + std::to_string(trolleyCount));

  // initializing insufficient funds text
  insufficientFundsText.setFont(font);
  insufficientFundsText.setCharacterSize(FONT_SIZE_COINS);
  insufficientFundsText.setFillColor(INSUFFICIENT_FUNDS_COLOR);
  insufficientFundsText.setPosition(
      800, 100);  // positioning it below the trolley count
  insufficientFundsText.setString("");  // initially it is set to empty

  // loading the trolley image
  if (!trolleyTexture.loadFromFile("Images/Trolley.png")) {
    std::cerr << "Error: Adult trolley image not found at Images/Trolley.png"
              << std::endl;
  }
  trolleySprite.setTexture(trolleyTexture);
  trolleySprite.setPosition(1700, 70);  // setting the position
  trolleySprite.setScale(0.5f, 0.5f);   // scaling the trolley

  // loading the shopping items
  loadItems();
}

// destructor to clean up the dynamically allocated window
AdultAvoShoppingWindow::~AdultAvoShoppingWindow() { delete window; }
void AdultAvoShoppingWindow::loadItems() {
  const int numRows = 2;  // Set to 2 rows for multiple items
  const int numCols = 3;  // Columns for item layout

  // loading each item with textures and setting positions
  std::vector<std::string> itemNames = {"Steak", "Fried Rice", "Curry Chicken",
                                        "Boba",  "Cold Rolls", "Medicine"};
  std::vector<int> itemPrices = {500, 200, 200, 150,
                                 180, 500};  // prices for the adult  avo items
  std::vector<std::string> imagePaths = {
      "Images/Steak.png", "Images/FriedRice.png", "Images/Curry.png",
      "Images/Boba.png",  "Images/ColdRolls.png", "Images/Medicine.png"};

  // calculating the total width and height for items and ensuring spacing in
  // them
  int totalWidth = numCols * ITEM_SIZE + (numCols - 1) * HORIZONTAL_SPACING;
  int totalHeight = numRows * ITEM_SIZE + (numRows - 1) * VERTICAL_SPACING;

  // calculating the top left corner to start placing the items
  int startX = (WINDOW_WIDTH - totalWidth) / 2 - totalWidth / 4;
  int startY = (WINDOW_HEIGHT - totalHeight) / 2 - totalHeight / 4;

  for (int index = 0; index < itemNames.size(); ++index) {
    Item item;
    item.name = itemNames[index];
    item.price = itemPrices[index];

    // Create and load texture into shared_ptr
    item.texture = std::make_shared<sf::Texture>();
    if (!item.texture->loadFromFile(imagePaths[index])) {
      std::cout << "Error: " << itemNames[index] << " image not found at "
                << imagePaths[index] << std::endl;
    }

    // setting the textures to sprites
    item.sprite.setTexture(*item.texture);

    // calculating  and setting the sprite position
    int col = index % numCols;
    int row = index / numCols;

    // Calculating the x and y positions for each item based on its row and
    // column
    int xPos = startX + col * (ITEM_SIZE + HORIZONTAL_SPACING);
    int yPos = startY + row * (ITEM_SIZE + VERTICAL_SPACING);

    // Setting sprite position
    item.sprite.setPosition(xPos, yPos);

    // Scaling items
    item.sprite.setScale(
        static_cast<float>(ITEM_SIZE) / item.sprite.getGlobalBounds().width,
        static_cast<float>(ITEM_SIZE) / item.sprite.getGlobalBounds().height);

    std::cout << "Loaded " << item.name << " at position (" << xPos << ", "
              << yPos << ")" << std::endl;

    // adding items to the vector items
    items.push_back(item);
  }
}

// Open the shopping window
void AdultAvoShoppingWindow::open() {
  while (window->isOpen()) {
    handleEvents();
    render();
  }
}

// function to handle window events
void AdultAvoShoppingWindow::handleEvents() {
  sf::Event event;

  while (window->pollEvent(event)) {
    // closing the wnidow if the events are closed
    if (event.type == sf::Event::Closed) {
      window->close();
    }
    // registering the button pressed event
    if (event.type == sf::Event::MouseButtonPressed) {
      // getting position of the mouse click
      sf::Vector2i clickPos = sf::Mouse::getPosition(*window);
      int x = clickPos.x;
      int y = clickPos.y;

      // insufficient funds message
      insufficientFundsText.setString("");

      // Checking if any item was clicked using loop
      for (auto& item : items) {
        sf::FloatRect bounds = item.sprite.getGlobalBounds();
        if (bounds.contains(static_cast<float>(x), static_cast<float>(y))) {
          if (userCoins >= item.price) {
            userCoins -= item.price;
            basket.push_back(item);
            trolleyCount++;  // Increment trolley count
            std::cout << "Purchased: " << item.name << std::endl;

            // Updating coins and trolley texts
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

// Rendering the shopping window
void AdultAvoShoppingWindow::render() {
  window->clear(BACKGROUND_COLOR);  // Setting background color

  window->draw(coinsText);    // displaying coins
  window->draw(trolleyText);  // displaying trolley count

  // drawing the trolley image
  window->draw(trolleySprite);  // rendernig the trolley sprite

  // drawing each item and displaying item name and price
  for (const auto& item : items) {
    window->draw(item.sprite);

    sf::Text itemText;
    itemText.setFont(font);
    itemText.setCharacterSize(FONT_SIZE_ITEM);
    itemText.setFillColor(sf::Color::Black);
    itemText.setPosition(item.sprite.getPosition().x,
                         item.sprite.getPosition().y +
                             item.sprite.getGlobalBounds().height + 10);
    itemText.setString(item.name + " - " + std::to_string(item.price) +
                       " coins");
    itemText.setCharacterSize(34);
    window->draw(itemText);
  }

  // Drawing the insufficient funds message if any
  window->draw(insufficientFundsText);

  window->display();
}
