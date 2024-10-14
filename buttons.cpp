#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "AdultAvoWindow.h"
#include "AdultGhostWindow.h"
#include "Animation.h"
#include "BabyAvoWindow.h"
#include "BabyGhostWindow.h"
#include "EatingAdultGhostWindow.h"
#include "EatingBabyAvo.h"
#include "EatingBabyGhost.h"
#include "Item.h"
#include "MATHGAME.h"
#include "adult_avo.h"
#include "adult_ghost.h"
#include "avo.h"
#include "baby_avo.h"
#include "baby_ghost.h"
#include "ghost.h"
#include "mini_game.h"
#include "pet_stats.h"
#include "quotesFile.h"
#include "sprite_loader.h"
int main() {
  sf::Font font;
  if (!font.loadFromFile("Regular.ttf")) {
    std::cout << "Font Not Found" << std::endl;
    return -1;
  }
  sf::Music backgroundMusic;
  if (!backgroundMusic.openFromFile("main_background_music.mp3")) {
    std::cout << "Music file not found" << std::endl;
    return -1;
  }
  backgroundMusic.setLoop(true);
  backgroundMusic.play();

  // creating main window
  sf::RenderWindow main_window(sf::VideoMode(1920, 1080), "My Virtual Pet");
  main_window.setFramerateLimit(60);
  std::string user_pet = SpriteLoader::show_intro_screen(main_window, font);
  main_window.display();
  std::cout << "User selected pet: " << user_pet << std::endl;
  PetStats* current_user_pet = SpriteLoader::initialize_pet(user_pet);
  PetStats petStats;

  // creating buttons
  if (!SpriteLoader::loadResources()) {
    std::cout << "error loading sprites" << std::endl;
  }

  std::string selectedQuote = getRandomQuote(user_pet);
  // main loop of game
  while (main_window.isOpen()) {
    sf::Event event;
    petStats.updateStats(main_window, font);

    updateQuote(selectedQuote, quote_clock, newQuoteInterval, user_pet,
                quoteVisible);
    while (main_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        main_window.close();
        return 0;
      }

      // checking if user clicked the icon
      if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i click_position = sf::Mouse::getPosition(main_window);
        int x = click_position.x;
        int y = click_position.y;
        if (x >= 40 && x <= 190 && y >= 130 && y <= 280) {
          std::cout << "Sleeping Button" << std::endl;
          petStats.maxSleep();
          SpriteLoader::animateSleepingPet(user_pet, main_window, font,
                                           selectedQuote, &petStats);
        } else if (x >= 470 && x <= 620 && y >= 130 && y <= 280) {
          std::cout << "showering Button" << std::endl;
          petStats.maxHealth();
          SpriteLoader::animateShoweringPet(user_pet, main_window, font,
                                            selectedQuote, &petStats);
        } else if (x >= 900 && x <= 1050 && y >= 130 && y <= 280) {
          std::cout << "Game Button" << std::endl;
          backgroundMusic.pause();
          mini_game new_game;
          while (new_game.window_open()) {
            new_game.update();
            new_game.render();
          }
          petStats.changeMoney(new_game.money_earned_end());
          backgroundMusic.play();
        } else if (x >= 1310 && x <= 1460 && y >= 130 && y <= 280) {
          std::cout << "Eating Button" << std::endl;
          int basketCapacity = 10;
          int basketSize = 0;
          ItemList* basket = new ItemList[basketCapacity];

          // Initialize the basket
          std::vector<std::string> initialItems = {
              "Steak", "Fried Rice", "Curry Chicken",
              "Boba",  "Cold Rolls", "Medicine"};
          std::vector<int> initialPrices = {500, 200, 200, 150, 180, 500};
          std::vector<int> initialStocks = {5, 5, 5, 5, 5, 5};

          for (size_t i = 0; i < initialItems.size(); ++i) {
            basket[basketSize].name = initialItems[i];
            basket[basketSize].price = initialPrices[i];
            basket[basketSize].stock = initialStocks[i];
            basket[basketSize].texture = nullptr;
            basket[basketSize].sprite = sf::Sprite();
            basket[basketSize].quantityText = sf::Text();
            basketSize++;
          }

          int trolleyCount = 0;  // Initialize trolley count
          if (user_pet == "adult_avo") {
            // Create an instance of the EatingAdultAvo class
            EatingAdultAvo eatingWindow(font, basket, basketSize,
                                        basketCapacity, trolleyCount);
            eatingWindow.open();  // Open the eating window
            delete[] basket;
          } else if (user_pet == "baby_avo") {
            EatingBabyAvo eatingWindow(font, basket, basketSize, basketCapacity,
                                       trolleyCount);

            // Open the window and run the application
            eatingWindow.open();

            // Clean up dynamically allocated memory
            delete[] basket;

          } else if (user_pet == "baby_ghost") {
            EatingAdultGhostWindow eatingWindow(font, basket, basketSize,
                                                basketCapacity, trolleyCount);

            // Open the window and run the application
            eatingWindow.open();

            // Clean up dynamically allocated memory
            delete[] basket;

          } else if (user_pet == "adult_ghost") {
            EatingBabyGhost eatingWindow(font, basket, basketSize,
                                         basketCapacity, trolleyCount);

            // Open the window and run the application
            eatingWindow.open();

            // Clean up dynamically allocated memory
            delete[] basket;
          }
          petStats.maxHunger();
          SpriteLoader::animateEatingPet(user_pet, main_window, font,
                                         selectedQuote, &petStats);
        } else if (x >= 40 && x <= 190 && y >= 680 && y <= 830) {
          std::cout << "Medicine Button" << std::endl;
          petStats.maxHealth();
          SpriteLoader::animateGivingMedicine(user_pet, main_window, font,
                                              selectedQuote, &petStats);
        } else if (x >= 470 && x <= 620 && y >= 680 && y <= 830) {
          std::cout << "Shopping Button" << std::endl;
          //youre part brookyln
          if (user_pet=="adult_avo"){
                std::vector<Item> basket; // User's shopping basket
               // Create an instance of the shopping window
              AdultAvoShoppingWindow shoppingWindow(font, petStats.getMoney(), basket);
              std::cout << "Shopping window created." << std::endl;
              shoppingWindow.open();
              
          }
          else if(user_pet=="baby_avo"){
            std::vector<Item> basket; // Basket to hold purchased items
           // Create BabyAvo instance
            BabyAvo shop(font, petStats.getMoney(), basket);
            std::cout << "Shopping window created." << std::endl;
            shop.open();
            
          } else if (user_pet == "baby_ghost") {
            std::vector<Item> basket;
            BabyGhostShoppingWindow shoppingWindow(font, petStats.getMoney(),
                                                   basket);
            // Open the window
            shoppingWindow.open();
         

          } else if (user_pet == "adult_ghost") {
            std::vector<Item> basket;
            AdultGhostWindow AdultGhostWindow(font, petStats.getMoney(),
                                              basket);

            // Open the shopping window
            AdultGhostWindow.open();
          }
        } else if (x >= 900 && x <= 1050 && y >= 680 && y <= 830) {
          backgroundMusic.pause();
          std::cout << "Math Button" << std::endl;
          math_game test;
          petStats.increaseIQ(test.getScore());
          // petStats.changeIQ(test);
          backgroundMusic.play();
        } else if (x >= 1310 && x <= 1460 && y >= 680 && y <= 830) {
          std::cout << "Info Button" << std::endl;
        } else if (x >= 650 && x <= 900 && y >= 400 && y <= 600) {
          std::cout << "Touch character" << std::endl;
          current_user_pet->make_sound();
        }
      }
    }
    SpriteLoader::drawSprites(main_window);
    petStats.renderStats(main_window, font);
    renderQuote(main_window, font, selectedQuote);
    if (user_pet == "adult_avo") {
      main_window.draw(SpriteLoader::adult_avo_normal_sprite);
    } else if (user_pet == "baby_avo") {
      main_window.draw(SpriteLoader::baby_avo_normal_sprite);
    } else if (user_pet == "adult_ghost") {
      main_window.draw(SpriteLoader::adult_ghost_normal_sprite);
    } else {
      main_window.draw(SpriteLoader::baby_ghost_normal_sprite);
    }
    petStats.checkStats(main_window, font);
    main_window.display();
  }
  return 0;
}
