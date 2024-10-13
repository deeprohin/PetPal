#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <memory> // Include for smart pointers

#include "adult_ghost.h"
#include "baby_avo.h"
#include "adult_avo.h"
#include "baby_ghost.h"
#include "Animation.h"
#include "MATHGAME.h"
#include "mini_game.h"
#include "pet_stats.h"
#include "quotesFile.h"
#include "sprite_loader.h"
#include "avo.h"
#include "ghost.h"
#include "Shopping.h"            // Include for shopping functionality
#include "eatingShop.h"           // Include for eating functionality
#include "GenericShoppingWindow.h"// Include for generic shopping window
#include "GenericEatingWindow.h"  // Include for generic eating window
#include "BaseItem.h"             // Include for base item class
#include "FoodItem.h"             // Include for food item class
#include "ShoppingBasket.h"       // Include shopping basket header

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

    // Creating the main window
    sf::RenderWindow main_window(sf::VideoMode(1920, 1080), "My Virtual Pet");
    main_window.setFramerateLimit(60);

    std::string user_pet = SpriteLoader::show_intro_screen(main_window, font);
    main_window.display();
    std::cout << "User selected pet: " << user_pet << std::endl;

    PetStats* current_user_pet = SpriteLoader::initialize_pet(user_pet);
    PetStats petStats;

    // Creating buttons and loading resources
    if (!SpriteLoader::loadResources()) {
        std::cout << "Error loading sprites" << std::endl;
    }

    std::string selectedQuote = getRandomQuote(user_pet);
    sf::Clock quote_clock;         // Initialize quote clock
    float newQuoteInterval = 10.0f; // Example interval
    bool quoteVisible = true;      // Example flag

    // Initialize Shopping and Eating
    bool isBaby = (user_pet == "baby_avo" || user_pet == "baby_ghost");
    Shopping shopping(isBaby);
    Eating eating(isBaby);

    int userCoins = 1000; // Starting coins
    ShoppingBasket shoppingBasket(10); // Shopping basket with initial capacity

    // Add items to the shopping basket
    shoppingBasket.addItem(std::make_shared<FoodItem>("Baby Milk", 50, 5));
    shoppingBasket.addItem(std::make_shared<FoodItem>("Baby Porridge", 30, 10));
    shoppingBasket.addItem(std::make_shared<FoodItem>("Baby Medicine", 500, 2));

    // Initialize Generic Shopping and Eating Windows
    GenericShoppingWindow genericShoppingWindow(font, userCoins, shoppingBasket, shopping);
    GenericEatingWindow genericEatingWindow(font, shoppingBasket, eating);

    // Main game loop
    while (main_window.isOpen()) {
        sf::Event event;
        petStats.updateStats(main_window, font);

        updateQuote(selectedQuote, quote_clock, newQuoteInterval, user_pet, quoteVisible);
        while (main_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                main_window.close();
                return 0;
            }

            // Checking if the user clicked on the icon
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i click_position = sf::Mouse::getPosition(main_window);
                int x = click_position.x;
                int y = click_position.y;
                
                if (x >= 40 && x <= 190 && y >= 130 && y <= 280) {
                    std::cout << "Sleeping Button" << std::endl;
                    petStats.maxSleep();
                    SpriteLoader::animateSleepingPet(user_pet, main_window, font, selectedQuote, &petStats);
                } else if (x >= 470 && x <= 620 && y >= 130 && y <= 280) {
                    std::cout << "Showering Button" << std::endl;
                    petStats.maxHealth();
                    SpriteLoader::animateShoweringPet(user_pet, main_window, font, selectedQuote, &petStats);
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
                    petStats.maxHunger();
                    SpriteLoader::animateEatingPet(user_pet, main_window, font, selectedQuote, &petStats);
                } else if (x >= 40 && x <= 190 && y >= 680 && y <= 830) {
                    std::cout << "Medicine Button" << std::endl;
                    petStats.maxHealth();
                    SpriteLoader::animateGivingMedicine(user_pet, main_window, font, selectedQuote, &petStats);
                } else if (x >= 470 && x <= 620 && y >= 680 && y <= 830) {
                    std::cout << "Shopping Button" << std::endl;
                    genericShoppingWindow.open();  // Brooklyn's part - Opens shopping window
                } else if (x >= 900 && x <= 1050 && y >= 680 && y <= 830) {
                    backgroundMusic.pause();
                    std::cout << "Math Button" << std::endl;
                    math_game test;
                    while (test.window_open()) {
                        test.update();
                        test.render();
                    }
                    petStats.increaseIQ(test.getScore());
                    backgroundMusic.play();
                } else if (x >= 1310 && x <= 1460 && y >= 680 && y <= 830) {
                    std::cout << "Info Button" << std::endl;
                } else if (x >= 650 && x <= 900 && y >= 400 && y <= 600) {
                    std::cout << "Touch Character" << std::endl;
                    current_user_pet->make_sound();
                }
            }
        }

        // Render Sprites, Stats, and Quotes
        SpriteLoader::drawSprites(main_window);
        petStats.renderStats(main_window, font);
        renderQuote(main_window, font, selectedQuote);

        // Draw selected pet's sprite
        if (user_pet == "adult_avo") {
            main_window.draw(SpriteLoader::adult_avo_normal_sprite);
        } else if (user_pet == "baby_avo") {
            main_window.draw(SpriteLoader::baby_avo_normal_sprite);
        } else if (user_pet == "adult_ghost") {
            main_window.draw(SpriteLoader::adult_ghost_normal_sprite);
        } else if (user_pet == "baby_ghost") {
            main_window.draw(SpriteLoader::baby_ghost_normal_sprite);
        }

        petStats.checkStats(main_window, font);
        main_window.display();
    }
    return 0;
}
