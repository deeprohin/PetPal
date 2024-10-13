#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

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

// Include Shopping and Eating classes
#include "Shopping.h"
#include "eatingShop.h"
#include "GenericShoppingWindow.h"
#include "GenericEatingWindow.h"
#include "Item.h"

// Function prototypes (implement these based on your project)
std::string getRandomQuote(const std::string& petType);
void updateQuote(std::string& quote, sf::Clock& clock, float interval, const std::string& petType, bool& visible);
void renderQuote(sf::RenderWindow& window, sf::Font& font, const std::string& quote);

int main() {
    // Load Font
    sf::Font font;
    if (!font.loadFromFile("Images/Regular.ttf")) {
        std::cout << "Font Not Found" << std::endl;
        return -1;
    }

    // Load Background Music
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("Images/main_background_music.mp3")) { 
        std::cout << "Music file not found" << std::endl;
        return -1;
    }
    backgroundMusic.setLoop(true); 
    backgroundMusic.play();

    // Create Main Window
    sf::RenderWindow main_window(sf::VideoMode(1920, 1080), "My Virtual Pet");
    main_window.setFramerateLimit(60);

    // Show Intro Screen and Get Selected Pet
    std::string user_pet = SpriteLoader::show_intro_screen(main_window, font);
    main_window.display();
    std::cout << "User selected pet: " << user_pet << std::endl;

    // Initialize Pet Stats
    PetStats petStats;

    // Load Resources
    if (!SpriteLoader::loadResources()) {
        std::cout << "Error loading sprites" << std::endl;
    }

    // Initialize Quote
    std::string selectedQuote = getRandomQuote(user_pet);
    sf::Clock quote_clock; // Initialize quote clock
    float newQuoteInterval = 10.0f; // Example interval
    bool quoteVisible = true; // Example flag

    // Determine if the pet is baby or adult
    bool isBaby = (user_pet == "baby_avo" || user_pet == "baby_ghost");

    // Initialize Shopping and Eating data
    Shopping shopping(isBaby);
    Eating eating(isBaby);

    // Initialize User Coins and Baskets
    int userCoins = 1000; // Starting coins
    std::vector<Item> shoppingBasket; // Shopping basket
    std::vector<Item> eatingBasket;   // Eating basket

    // Initialize Generic Shopping and Eating Windows
    GenericShoppingWindow genericShoppingWindow(font, userCoins, shoppingBasket, shopping);
    GenericEatingWindow genericEatingWindow(font, eatingBasket, eating);

    // Main Loop
    while (main_window.isOpen()) {
        sf::Event event;
        petStats.updateStats(main_window, font);

        updateQuote(selectedQuote, quote_clock, newQuoteInterval, user_pet, quoteVisible);
        while (main_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                main_window.close();
                return 0;
            }

            // Handling Mouse Clicks
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i click_position = sf::Mouse::getPosition(main_window);
                int x = click_position.x;
                int y = click_position.y;

                // Define button regions and actions
                if (x >= 40 && x <= 190 && y >= 130 && y <= 280) {
                    std::cout << "Sleeping Button" << std::endl;
                    petStats.maxSleep();
                    SpriteLoader::animateSleepingPet(user_pet, main_window, font, selectedQuote, &petStats);
                }
                else if (x >= 470 && x <= 620 && y >= 130 && y <= 280) {
                    std::cout << "Showering Button" << std::endl;
                    petStats.maxHealth();
                    SpriteLoader::animateShoweringPet(user_pet, main_window, font, selectedQuote, &petStats);
                }
                else if (x >= 900 && x <= 1050 && y >= 130 && y <= 280) {
                    std::cout << "Game Button" << std::endl;
                    backgroundMusic.pause();
                    mini_game new_game;
                    while (new_game.window_open()) { // Assuming window_open() returns true while the game is active
                        new_game.update();
                        new_game.render();
                    }
                    petStats.changeMoney(new_game.money_earned_end());
                    backgroundMusic.play();
                }
                else if (x >= 1310 && x <= 1460 && y >= 130 && y <= 280) {
                    std::cout << "Eating Button" << std::endl;
                    petStats.maxHunger();
                    
                    // Open Eating Window
                    genericEatingWindow.open();
                }
                else if (x >= 40 && x <= 190 && y >= 680 && y <= 830) {
                    std::cout << "Medicine Button" << std::endl;
                    petStats.maxHealth();
                    SpriteLoader::animateGivingMedicine(user_pet, main_window, font, selectedQuote, &petStats);
                }
                else if (x >= 470 && x <= 620 && y >= 680 && y <= 830) {
                    std::cout << "Shopping Button" << std::endl;
                    
                    // Open Shopping Window
                    genericShoppingWindow.open();
                }
                else if (x >= 900 && x <= 1050 && y >= 680 && y <= 830) {
                    backgroundMusic.pause();
                    std::cout << "Math Button" << std::endl;
                    math_game test;
                    while (test.window_open()) { // Assuming window_open() returns true while the game is active
                        test.update();
                        test.render();
                    }
                    petStats.increaseIQ(test.getScore());
                    backgroundMusic.play();
                }
                else if (x >= 1310 && x <= 1460 && y >= 680 && y <= 830) {
                    std::cout << "Info Button" << std::endl;
                    // Implement Info Button functionality
                }
                else if(x >= 650 && x <= 900 && y >= 400 && y <= 600){
                    std::cout << "Touch character" << std::endl;
                    // Assuming current_user_pet is properly initialized and points to the correct PetStats object
                    // If current_user_pet is not used, you might want to remove or replace this
                    // Example:
                    // current_user_pet->make_sound();
                }
            }
        }

        // Drawing and Rendering
        SpriteLoader::drawSprites(main_window);
        petStats.renderStats(main_window, font);
        renderQuote(main_window, font, selectedQuote);

        // Draw the selected pet's sprite
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
