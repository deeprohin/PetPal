#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Animation.h"
#include "MATHGAME.h"
#include "adult_avo.h"
#include "adult_ghost.h"
#include "baby_avo.h"
#include "baby_ghost.h"
#include "mini_game.h"
#include "pet_stats.h"
#include "quotesFile.h"
#include "sprite_loader.h"

std::string show_intro_screen(sf::RenderWindow& window, sf::Font& font) {
  // Load button textures
  sf::Texture avo_texture, ghost_texture;
  if (!avo_texture.loadFromFile("avoButton.png") ||
      !ghost_texture.loadFromFile("ghostButton.png")) {
    std::cout << "Button Images Not Found" << std::endl;
    return "";
  }

  // Create sprites for the buttons
  sf::Sprite avoButton(avo_texture);
  avoButton.setScale(0.02f, 0.02f);
  avoButton.setPosition(300, 400);  // Adjust position based on button size

  sf::Sprite ghostButton(ghost_texture);
  ghostButton.setScale(0.2f, 0.2f);
  ghostButton.setPosition(900, 400);  // Adjust position based on button size

  // Create text objects
  sf::Text title("Choose a Pet :)", font, 80);  // Title text
  title.setFillColor(sf::Color::Black);
  title.setPosition((window.getSize().x - title.getGlobalBounds().width) / 2,
                    50);  // Center the title

  sf::Text avoText("Avo", font, 50);  // Avo text
  avoText.setFillColor(sf::Color::Black);
  avoText.setPosition(300, 560);  // Position below the Avo button

  sf::Text ghostText("Ghost", font, 50);  // Ghost text
  ghostText.setFillColor(sf::Color::Black);
  ghostText.setPosition(900, 560);  // Position below the Ghost button

  // Text for selecting Adult or Baby
  sf::Text adultText("Adult", font, 40);
  adultText.setFillColor(sf::Color::Black);
  adultText.setPosition((window.getSize().x / 2) - 100,
                        700);  // Center below the options

  sf::Text babyText("Baby", font, 40);
  babyText.setFillColor(sf::Color::Black);
  babyText.setPosition((window.getSize().x / 2) + 50,
                       700);  // Center next to Adult

  bool inIntro = true;      // Track whether we are in the intro screen
  std::string selectedPet;  // To store the selected pet type

  while (inIntro) {
    sf::Event event;

    // Clear the window
    window.clear(sf::Color(230, 230, 220));

    // Draw the buttons
    window.draw(avoButton);
    window.draw(ghostButton);

    // Draw the title and button labels
    window.draw(title);
    window.draw(avoText);
    window.draw(ghostText);

    // If a pet is selected, show the Adult/Baby options
    if (!selectedPet.empty()) {
      window.draw(adultText);
      window.draw(babyText);
    }

    // Display the window contents
    window.display();

    // Event loop to handle user input
    while (window.pollEvent(event)) {
      std::cout << "test" << std::endl;
      if (event.type == sf::Event::Closed) {
        window.close();
        return "";
      }

      // Check if user clicked a button
      if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i click_position = sf::Mouse::getPosition(window);
        int x = click_position.x;
        int y = click_position.y;

        std::cout << "Mouse clicked at: " << x << ", " << y << std::endl;

        if (avoButton.getGlobalBounds().contains(x, y)) {
          std::cout << "Avocado selected!" << std::endl;
          selectedPet = "Avo";  // Set the selected pet type
        } else if (ghostButton.getGlobalBounds().contains(x, y)) {
          std::cout << "Ghost selected!" << std::endl;
          selectedPet = "Ghost";  // Set the selected pet type
        } else if (selectedPet == "Avo" &&
                   adultText.getGlobalBounds().contains(x, y)) {
          std::cout << "Adult Avo selected!" << std::endl;
          return "adult_avo";  // Return adult Avo
        } else if (selectedPet == "Avo" &&
                   babyText.getGlobalBounds().contains(x, y)) {
          std::cout << "Baby Avo selected!" << std::endl;
          return "baby_avo";  // Return baby Avo
        } else if (selectedPet == "Ghost" &&
                   adultText.getGlobalBounds().contains(x, y)) {
          std::cout << "Adult Ghost selected!" << std::endl;
          return "adult_ghost";  // Return adult Ghost
        } else if (selectedPet == "Ghost" &&
                   babyText.getGlobalBounds().contains(x, y)) {
          std::cout << "Baby Ghost selected!" << std::endl;
          return "baby_ghost";  // Return baby Ghost
        }
      }
    }
  }

  return "";  // Default return value
}

void display_buttons(sf::RenderWindow& window){
    sf::RectangleShape line(sf::Vector2f(1920, 5));
    line.setFillColor(sf::Color::Black);
    line.setPosition(0, 120);
}

int main() {
  sf::Font font;
  if (!font.loadFromFile("Regular.ttf")) {
    std::cout << "Font Not Found" << std::endl;
    return -1;
  }

  // creating main window
  sf::RenderWindow main_window(sf::VideoMode(1920, 1080), "My Virtual Pet");
  main_window.setFramerateLimit(60);
  std::string user_pet = show_intro_screen(main_window, font);
  main_window.display();
  std::cout << "User selected pet: " << user_pet << std::endl;
  PetStats petStats;


  // creating buttons
    sf::RectangleShape line(sf::Vector2f(1920, 5));
  line.setFillColor(sf::Color::Black);
  line.setPosition(0, 120);

  if (!SpriteLoader::loadResources()) {
    std::cout<<"error loading sprites"<<std::endl;
}
  std::string selectedQuote = getRandomQuote(user_pet);
  // main loop of game
  while (main_window.isOpen()) {
    sf::Event event;
    petStats.updateStats();

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
          if (user_pet == "adult_avo") {
            adult_avo sleeping("Big2/sleeping/spritesheet.png", 0.8f, 8.0f,
                               8.0f);
            sleeping.startAnimation_sleeping();
            sf::Clock clock;  // Clock to track time
            sf::Clock total_animation_time;
            while (main_window.isOpen()) {
              sf::Event event;
              while (main_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) main_window.close();
              }

              // Get the time elapsed since the last frame
              float deltaTime = clock.restart().asSeconds();

              // Update the Sleeping Sleeping
              sleeping.update_sleeping(deltaTime);

              // Clear the window
              main_window.clear(sf::Color(
                  230, 230,
                  220));  // Optionally change the color for better visibility

              // Draw the Sleeping sprite
              sleeping.draw_sleeping(main_window);
              main_window.draw(line);
              main_window.draw(SpriteLoader::sleeping_button_sprite);
              main_window.draw(SpriteLoader::shower_button_sprite);
              main_window.draw(SpriteLoader::game_button_sprite);
              main_window.draw(SpriteLoader::food_button_sprite);
              main_window.draw(SpriteLoader::health_button_sprite);
              main_window.draw(SpriteLoader::shopping_button_sprite);
              main_window.draw(SpriteLoader::info_button_sprite);
              main_window.draw(SpriteLoader::math_button_sprite);
              petStats.renderStats(main_window, font);
              renderQuote(main_window, font, selectedQuote);
              // Display the window contents

              main_window.display();
              if (total_animation_time.getElapsedTime().asSeconds() >= 6) {
                break;
              }
            }
          } else if (user_pet == "baby_avo") {
            baby_avo sleeping("Small2/Sleeping/spritesheet.png", 0.8f, 8.0f,
                              8.0f);
            sleeping.startAnimation_sleeping();
            sf::Clock clock;  // Clock to track time
            sf::Clock total_animation_time;
            while (main_window.isOpen()) {
              sf::Event event;
              while (main_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) main_window.close();
              }

              // Get the time elapsed since the last frame
              float deltaTime = clock.restart().asSeconds();

              // Update the Sleeping Sleeping
              sleeping.update_sleeping(deltaTime);

              // Clear the window
              main_window.clear(sf::Color(
                  230, 230,
                  220));  // Optionally change the color for better visibility

              // Draw the Sleeping sprite
              sleeping.draw_sleeping(main_window);
              main_window.draw(line);
              main_window.draw(SpriteLoader::sleeping_button_sprite);
              main_window.draw(SpriteLoader::shower_button_sprite);
              main_window.draw(SpriteLoader::game_button_sprite);
              main_window.draw(SpriteLoader::food_button_sprite);
              main_window.draw(SpriteLoader::health_button_sprite);
              main_window.draw(SpriteLoader::shopping_button_sprite);
              main_window.draw(SpriteLoader::info_button_sprite);
              main_window.draw(SpriteLoader::math_button_sprite);
              petStats.renderStats(main_window, font);
              renderQuote(main_window, font, selectedQuote);
              // Display the window contents
              main_window.display();
              if (total_animation_time.getElapsedTime().asSeconds() >= 6) {
                break;
              }
            }
          } else if (user_pet == "adult_ghost") {
            adult_ghost sleeping("Big/Sleeping.png", 0.8f, 8.0f, 8.0f);
            sleeping.startAnimation_sleeping();
            sf::Clock clock;  // Clock to track time
            sf::Clock total_animation_time;
            while (main_window.isOpen()) {
              sf::Event event;
              while (main_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) main_window.close();
              }

              // Get the time elapsed since the last frame
              float deltaTime = clock.restart().asSeconds();

              // Update the Sleeping Sleeping
              sleeping.update_sleeping(deltaTime);

              // Clear the window
              main_window.clear(sf::Color(
                  230, 230,
                  220));  // Optionally change the color for better visibility

              // Draw the Sleeping sprite
              sleeping.draw_sleeping(main_window);
              main_window.draw(line);
              main_window.draw(SpriteLoader::sleeping_button_sprite);
              main_window.draw(SpriteLoader::shower_button_sprite);
              main_window.draw(SpriteLoader::game_button_sprite);
              main_window.draw(SpriteLoader::food_button_sprite);
              main_window.draw(SpriteLoader::health_button_sprite);
              main_window.draw(SpriteLoader::shopping_button_sprite);
              main_window.draw(SpriteLoader::info_button_sprite);
              main_window.draw(SpriteLoader::math_button_sprite);
              petStats.renderStats(main_window, font);
              renderQuote(main_window, font, selectedQuote);

              // Display the window contents
              main_window.display();
              if (total_animation_time.getElapsedTime().asSeconds() >= 6) {
                break;
              }
            }
          } else if (user_pet == "baby_ghost") {
            baby_ghost sleeping("Small/Sleeping.png", 0.8f, 8.0f, 8.0f);
            sleeping.startAnimation_sleeping();
            sf::Clock clock;  // Clock to track time
            sf::Clock total_animation_time;
            while (main_window.isOpen()) {
              sf::Event event;
              while (main_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) main_window.close();
              }
              // Get the time elapsed since the last frame
              float deltaTime = clock.restart().asSeconds();
              // Update the Sleeping Sleeping
              sleeping.update_sleeping(deltaTime);
              // Clear the window
              main_window.clear(sf::Color(230, 230,220));  // Optionally change the color for better visibility

              // Draw the Sleeping sprite
              sleeping.draw_sleeping(main_window);
              main_window.draw(line);
              main_window.draw(SpriteLoader::sleeping_button_sprite);
              main_window.draw(SpriteLoader::shower_button_sprite);
              main_window.draw(SpriteLoader::game_button_sprite);
              main_window.draw(SpriteLoader::food_button_sprite);
              main_window.draw(SpriteLoader::health_button_sprite);
              main_window.draw(SpriteLoader::shopping_button_sprite);
              main_window.draw(SpriteLoader::info_button_sprite);
              main_window.draw(SpriteLoader::math_button_sprite);
              petStats.renderStats(main_window, font);
              renderQuote(main_window, font, selectedQuote);
              // Display the window contents
              main_window.display();
              if (total_animation_time.getElapsedTime().asSeconds() >= 6) {
                break;
              }
            }
          }
        } else if (x >= 470 && x <= 620 && y >= 130 && y <= 280) {
          std::cout << "showering Button" << std::endl;
          petStats.maxHealth();
          if (user_pet == "adult_avo") {
            adult_avo test("Big2/showering/spritesheet.png", 1.4f, 8.0f, 8.0f);
            test.startAnimation_shower();
            sf::Clock clock;  // Clock to track time
            sf::Clock total_animation_time;
            while (main_window.isOpen()) {
              sf::Event event;
              while (main_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                  main_window.close();
                }
              }
              // Get the time elapsed since the last frame
              float deltaTime = clock.restart().asSeconds();
              test.update_shower(deltaTime);
              // Draw the shower
              main_window.clear(sf::Color(230, 230, 220));
              test.draw_shower(main_window);
              main_window.draw(line);
              main_window.draw(SpriteLoader::sleeping_button_sprite);
              main_window.draw(SpriteLoader::shower_button_sprite);
              main_window.draw(SpriteLoader::game_button_sprite);
              main_window.draw(SpriteLoader::food_button_sprite);
              main_window.draw(SpriteLoader::health_button_sprite);
              main_window.draw(SpriteLoader::shopping_button_sprite);
              main_window.draw(SpriteLoader::info_button_sprite);
              main_window.draw(SpriteLoader::math_button_sprite);
              petStats.renderStats(main_window, font);
              renderQuote(main_window, font, selectedQuote);

              // Display the window contents
              main_window.display();
              if (total_animation_time.getElapsedTime().asSeconds() >= 6) {
                break;
              }
            }
          } else if (user_pet == "baby_avo") {
            baby_avo baby_showering("Small2/Showering/spritesheet.png", 0.8f,
                                    8.0f, 8.0f);
            baby_showering.startAnimation_shower();
            sf::Clock clock;  // Clock to track time
            sf::Clock total_animation_time;
            while (main_window.isOpen()) {
              sf::Event event;
              while (main_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) main_window.close();
              }

              // Get the time elapsed since the last frame
              float deltaTime = clock.restart().asSeconds();
              // Update the Sleeping Sleeping
              baby_showering.update_shower(deltaTime);
              // Clear the window
              main_window.clear(sf::Color(
                  230, 230,
                  220));  // Optionally change the color for better visibility

              // Draw the Sleeping sprite
              baby_showering.draw_shower(main_window);
              main_window.draw(line);
              main_window.draw(SpriteLoader::sleeping_button_sprite);
              main_window.draw(SpriteLoader::shower_button_sprite);
              main_window.draw(SpriteLoader::game_button_sprite);
              main_window.draw(SpriteLoader::food_button_sprite);
              main_window.draw(SpriteLoader::health_button_sprite);
              main_window.draw(SpriteLoader::shopping_button_sprite);
              main_window.draw(SpriteLoader::info_button_sprite);
              main_window.draw(SpriteLoader::math_button_sprite);
              petStats.renderStats(main_window, font);
              renderQuote(main_window, font, selectedQuote);
              // Display the window contents
              main_window.display();
              if (total_animation_time.getElapsedTime().asSeconds() >= 6) {
                break;
              }
            }
          } else if (user_pet == "adult_ghost") {
            adult_ghost adult_ghost_showering("Big/Shower.png", 0.8f, 8.0f,
                                              8.0f);
            adult_ghost_showering.startAnimation_shower();
            sf::Clock clock;  // Clock to track time
            sf::Clock total_animation_time;
            while (main_window.isOpen()) {
              sf::Event event;
              while (main_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) main_window.close();
              }

              // Get the time elapsed since the last frame
              float deltaTime = clock.restart().asSeconds();
              // Update the Sleeping Sleeping
              adult_ghost_showering.update_shower(deltaTime);
              // Clear the window
              main_window.clear(sf::Color(
                  230, 230,
                  220));  // Optionally change the color for better visibility

              // Draw the Sleeping sprite
              adult_ghost_showering.draw_shower(main_window);
              main_window.draw(line);
              main_window.draw(SpriteLoader::sleeping_button_sprite);
              main_window.draw(SpriteLoader::shower_button_sprite);
              main_window.draw(SpriteLoader::game_button_sprite);
              main_window.draw(SpriteLoader::food_button_sprite);
              main_window.draw(SpriteLoader::health_button_sprite);
              main_window.draw(SpriteLoader::shopping_button_sprite);
              main_window.draw(SpriteLoader::info_button_sprite);
              main_window.draw(SpriteLoader::math_button_sprite);
              petStats.renderStats(main_window, font);
              renderQuote(main_window, font, selectedQuote);
              // Display the window contents
              main_window.display();
              if (total_animation_time.getElapsedTime().asSeconds() >= 6) {
                break;
              }
            }
          } else if (user_pet == "baby_ghost") {
            baby_ghost adult_ghost_showering("Small/Shower.png", 0.8f, 8.0f,
                                             8.0f);
            adult_ghost_showering.startAnimation_shower();
            sf::Clock clock;  // Clock to track time
            sf::Clock total_animation_time;
            while (main_window.isOpen()) {
              sf::Event event;
              while (main_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) main_window.close();
              }

              // Get the time elapsed since the last frame
              float deltaTime = clock.restart().asSeconds();
              // Update the Sleeping Sleeping
              adult_ghost_showering.update_shower(deltaTime);
              // Clear the window
              main_window.clear(sf::Color(
                  230, 230,
                  220));  // Optionally change the color for better visibility

              // Draw the Sleeping sprite
              adult_ghost_showering.draw_shower(main_window);
              main_window.draw(line);
              main_window.draw(SpriteLoader::sleeping_button_sprite);
              main_window.draw(SpriteLoader::shower_button_sprite);
              main_window.draw(SpriteLoader::game_button_sprite);
              main_window.draw(SpriteLoader::food_button_sprite);
              main_window.draw(SpriteLoader::health_button_sprite);
              main_window.draw(SpriteLoader::shopping_button_sprite);
              main_window.draw(SpriteLoader::info_button_sprite);
              main_window.draw(SpriteLoader::math_button_sprite);
              petStats.renderStats(main_window, font);
              renderQuote(main_window, font, selectedQuote);
              // Display the window contents
              main_window.display();
              if (total_animation_time.getElapsedTime().asSeconds() >= 6) {
                break;
              }
            }
          }
        } else if (x >= 900 && x <= 1050 && y >= 130 && y <= 280) {
          std::cout << "Game Button" << std::endl;
          mini_game new_game;
          while (new_game.window_open()) {
            new_game.update();
            new_game.render();
          }
          petStats.changeMoney(new_game.money_earned_end());

        } else if (x >= 1310 && x <= 1460 && y >= 130 && y <= 280) {
          std::cout << "Eating Button" << std::endl;
          petStats.maxHunger();
          if (user_pet == "adult_avo") {
            adult_avo adult_avo_eating("Big2/Eating/spritesheet.png", 1.4f,
                                       8.0f, 8.0f);
            adult_avo_eating.startAnimation_eating();
            sf::Clock clock1;  // Clock to track time
            sf::Clock total_animation_time1;
            while (main_window.isOpen()) {
              sf::Event event;
              while (main_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                  main_window.close();
                }
              }
              // Get the time elapsed since the last frame
              float deltaTime = clock1.restart().asSeconds();
              adult_avo_eating.update_eating(deltaTime);

              // Draw the shower
              main_window.clear(sf::Color(230, 230, 220));
              adult_avo_eating.draw_eating(main_window);
              main_window.draw(line);
              main_window.draw(SpriteLoader::sleeping_button_sprite);
              main_window.draw(SpriteLoader::shower_button_sprite);
              main_window.draw(SpriteLoader::game_button_sprite);
              main_window.draw(SpriteLoader::food_button_sprite);
              main_window.draw(SpriteLoader::health_button_sprite);
              main_window.draw(SpriteLoader::shopping_button_sprite);
              main_window.draw(SpriteLoader::info_button_sprite);
              main_window.draw(SpriteLoader::math_button_sprite);
              petStats.renderStats(main_window, font);
              renderQuote(main_window, font, selectedQuote);

              // Display the window contents
              main_window.display();
              if (total_animation_time1.getElapsedTime().asSeconds() >= 6) {
                break;
              }
            }
          } else if (user_pet == "baby_avo") {
            baby_avo eating("Small2/Eating/spritesheet.png", 1.4f, 8.0f, 8.0f);
            eating.startAnimation_eating();
            sf::Clock clock1;  // Clock to track time
            sf::Clock total_animation_time1;
            while (main_window.isOpen()) {
              sf::Event event;
              while (main_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                  main_window.close();
                }
              }
              // Get the time elapsed since the last frame
              float deltaTime = clock1.restart().asSeconds();
              eating.update_eating(deltaTime);

              // Draw the shower
              main_window.clear(sf::Color(230, 230, 220));
              eating.draw_eating(main_window);
              main_window.draw(line);
              main_window.draw(SpriteLoader::sleeping_button_sprite);
              main_window.draw(SpriteLoader::shower_button_sprite);
              main_window.draw(SpriteLoader::game_button_sprite);
              main_window.draw(SpriteLoader::food_button_sprite);
              main_window.draw(SpriteLoader::health_button_sprite);
              main_window.draw(SpriteLoader::shopping_button_sprite);
              main_window.draw(SpriteLoader::info_button_sprite);
              main_window.draw(SpriteLoader::math_button_sprite);
              petStats.renderStats(main_window, font);
              renderQuote(main_window, font, selectedQuote);

              // Display the window contents
              main_window.display();
              if (total_animation_time1.getElapsedTime().asSeconds() >= 6) {
                break;
              }
            }
          } else if (user_pet == "adult_ghost") {
            adult_ghost eating("Big/eating.png", 1.4f, 8.0f, 8.0f);
            eating.startAnimation_eating();
            sf::Clock clock1;  // Clock to track time
            sf::Clock total_animation_time1;
            while (main_window.isOpen()) {
              sf::Event event;
              while (main_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                  main_window.close();
                }
              }
              // Get the time elapsed since the last frame
              float deltaTime = clock1.restart().asSeconds();
              eating.update_eating(deltaTime);

              // Draw the shower
              main_window.clear(sf::Color(230, 230, 220));
              eating.draw_eating(main_window);
              main_window.draw(line);
              main_window.draw(SpriteLoader::sleeping_button_sprite);
              main_window.draw(SpriteLoader::shower_button_sprite);
              main_window.draw(SpriteLoader::game_button_sprite);
              main_window.draw(SpriteLoader::food_button_sprite);
              main_window.draw(SpriteLoader::health_button_sprite);
              main_window.draw(SpriteLoader::shopping_button_sprite);
              main_window.draw(SpriteLoader::info_button_sprite);
              main_window.draw(SpriteLoader::math_button_sprite);
              petStats.renderStats(main_window, font);
              renderQuote(main_window, font, selectedQuote);

              // Display the window contents
              main_window.display();
              if (total_animation_time1.getElapsedTime().asSeconds() >= 6) {
                break;
              }
            }
          } else if (user_pet == "baby_ghost") {
            baby_ghost eating("Small/eating.png", 1.4f, 8.0f, 8.0f);
            eating.startAnimation_eating();
            sf::Clock clock1;  // Clock to track time
            sf::Clock total_animation_time1;
            while (main_window.isOpen()) {
              sf::Event event;
              while (main_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                  main_window.close();
                }
              }
              // Get the time elapsed since the last frame
              float deltaTime = clock1.restart().asSeconds();
              eating.update_eating(deltaTime);

              // Draw the shower
              main_window.clear(sf::Color(230, 230, 220));
              eating.draw_eating(main_window);
              main_window.draw(line);
              main_window.draw(SpriteLoader::sleeping_button_sprite);
              main_window.draw(SpriteLoader::shower_button_sprite);
              main_window.draw(SpriteLoader::game_button_sprite);
              main_window.draw(SpriteLoader::food_button_sprite);
              main_window.draw(SpriteLoader::health_button_sprite);
              main_window.draw(SpriteLoader::shopping_button_sprite);
              main_window.draw(SpriteLoader::info_button_sprite);
              main_window.draw(SpriteLoader::math_button_sprite);
              petStats.renderStats(main_window, font);
              renderQuote(main_window, font, selectedQuote);

              // Display the window contents
              main_window.display();
              if (total_animation_time1.getElapsedTime().asSeconds() >= 6) {
                break;
              }
            }
          }
        } else if (x >= 40 && x <= 190 && y >= 680 && y <= 830) {
          std::cout << "Medicine Button" << std::endl;
          petStats.maxHealth();
          if (user_pet == "adult_avo") {
            adult_avo adult_avo_meds("New Piskel-1 10.15.48ΓÇ»PM.png (2).png",
                                     1.4f, 8.0f, 8.0f);
            adult_avo_meds.startAnimation_medicine();
            sf::Clock clock1;  // Clock to track time
            sf::Clock total_animation_time1;
            while (main_window.isOpen()) {
              sf::Event event;
              while (main_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                  main_window.close();
                }
              }
              // Get the time elapsed since the last frame
              float deltaTime = clock1.restart().asSeconds();
              adult_avo_meds.update_medicine(deltaTime);
              // Draw the shower
              main_window.clear(sf::Color(230, 230, 220));
              adult_avo_meds.draw_medicine(main_window);
              main_window.draw(line);
              main_window.draw(SpriteLoader::sleeping_button_sprite);
              main_window.draw(SpriteLoader::shower_button_sprite);
              main_window.draw(SpriteLoader::game_button_sprite);
              main_window.draw(SpriteLoader::food_button_sprite);
              main_window.draw(SpriteLoader::health_button_sprite);
              main_window.draw(SpriteLoader::shopping_button_sprite);
              main_window.draw(SpriteLoader::info_button_sprite);
              main_window.draw(SpriteLoader::math_button_sprite);
              petStats.renderStats(main_window, font);
              renderQuote(main_window, font, selectedQuote);

              // Display the window contents
              main_window.display();
              if (total_animation_time1.getElapsedTime().asSeconds() >= 6) {
                break;
              }
            }
          } else if (user_pet == "baby_avo") {
            baby_avo meds("Small2/medications/spritesheet.png", 1.4f, 8.0f,
                          8.0f);
            meds.startAnimation_medicine();
            sf::Clock clock1;  // Clock to track time
            sf::Clock total_animation_time1;
            while (main_window.isOpen()) {
              sf::Event event;
              while (main_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                  main_window.close();
                }
              }
              // Get the time elapsed since the last frame
              float deltaTime = clock1.restart().asSeconds();
              meds.update_medicine(deltaTime);
              // Draw the shower
              main_window.clear(sf::Color(230, 230, 220));
              meds.draw_medicine(main_window);
              main_window.draw(line);
              main_window.draw(SpriteLoader::sleeping_button_sprite);
              main_window.draw(SpriteLoader::shower_button_sprite);
              main_window.draw(SpriteLoader::game_button_sprite);
              main_window.draw(SpriteLoader::food_button_sprite);
              main_window.draw(SpriteLoader::health_button_sprite);
              main_window.draw(SpriteLoader::shopping_button_sprite);
              main_window.draw(SpriteLoader::info_button_sprite);
              main_window.draw(SpriteLoader::math_button_sprite);
              petStats.renderStats(main_window, font);

              // Display the window contents
              main_window.display();
              if (total_animation_time1.getElapsedTime().asSeconds() >= 6) {
                break;
              }
            }
          } else if (user_pet == "adult_ghost") {
            adult_ghost meds("Big/Medicine .png", 1.4f, 8.0f, 8.0f);
            meds.startAnimation_medicine();
            sf::Clock clock1;  // Clock to track time
            sf::Clock total_animation_time1;
            while (main_window.isOpen()) {
              sf::Event event;
              while (main_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                  main_window.close();
                }
              }
              // Get the time elapsed since the last frame
              float deltaTime = clock1.restart().asSeconds();
              meds.update_medicine(deltaTime);
              // Draw the shower
              main_window.clear(sf::Color(230, 230, 220));
              meds.draw_medicine(main_window);
              main_window.draw(line);
              main_window.draw(SpriteLoader::sleeping_button_sprite);
              main_window.draw(SpriteLoader::shower_button_sprite);
              main_window.draw(SpriteLoader::game_button_sprite);
              main_window.draw(SpriteLoader::food_button_sprite);
              main_window.draw(SpriteLoader::health_button_sprite);
              main_window.draw(SpriteLoader::shopping_button_sprite);
              main_window.draw(SpriteLoader::info_button_sprite);
              main_window.draw(SpriteLoader::math_button_sprite);
              petStats.renderStats(main_window, font);
              renderQuote(main_window, font, selectedQuote);
              // Display the window contents
              main_window.display();
              if (total_animation_time1.getElapsedTime().asSeconds() >= 6) {
                break;
              }
            }
          } else if (user_pet == "baby_ghost") {
            baby_ghost meds("Small/Medicine .png", 1.4f, 8.0f, 8.0f);
            meds.startAnimation_medicine();
            sf::Clock clock1;  // Clock to track time
            sf::Clock total_animation_time1;
            while (main_window.isOpen()) {
              sf::Event event;
              while (main_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                  main_window.close();
                }
              }
              // Get the time elapsed since the last frame
              float deltaTime = clock1.restart().asSeconds();
              meds.update_medicine(deltaTime);
              // Draw the shower
              main_window.clear(sf::Color(230, 230, 220));
              meds.draw_medicine(main_window);
              main_window.draw(line);
              main_window.draw(SpriteLoader::sleeping_button_sprite);
              main_window.draw(SpriteLoader::shower_button_sprite);
              main_window.draw(SpriteLoader::game_button_sprite);
              main_window.draw(SpriteLoader::food_button_sprite);
              main_window.draw(SpriteLoader::health_button_sprite);
              main_window.draw(SpriteLoader::shopping_button_sprite);
              main_window.draw(SpriteLoader::info_button_sprite);
              main_window.draw(SpriteLoader::math_button_sprite);
              petStats.renderStats(main_window, font);
              renderQuote(main_window, font, selectedQuote);

              // Display the window contents
              main_window.display();
              if (total_animation_time1.getElapsedTime().asSeconds() >= 6) {
                break;
              }
            }
          }
        } else if (x >= 470 && x <= 620 && y >= 680 && y <= 830) {
          std::cout << "Shopping Button" << std::endl;
        } else if (x >= 900 && x <= 1050 && y >= 680 && y <= 830) {
          std::cout << "Math Button" << std::endl;
          math_game test;
        } else if (x >= 1310 && x <= 1460 && y >= 680 && y <= 830) {
          std::cout << "Info Button" << std::endl;
        }
      }
    }
    main_window.clear(sf::Color(230, 230, 220));
    main_window.draw(line);
    main_window.draw(SpriteLoader::sleeping_button_sprite);
    main_window.draw(SpriteLoader::shower_button_sprite);
    main_window.draw(SpriteLoader::game_button_sprite);
    main_window.draw(SpriteLoader::food_button_sprite);
    main_window.draw(SpriteLoader::health_button_sprite);
    main_window.draw(SpriteLoader::shopping_button_sprite);
    main_window.draw(SpriteLoader::info_button_sprite);
    main_window.draw(SpriteLoader::math_button_sprite);
    petStats.renderStats(main_window, font);
    renderQuote(main_window, font, selectedQuote);
    if(user_pet=="adult_avo"){
    main_window.draw(SpriteLoader::adult_avo_normal_sprite);
    }else if(user_pet=="baby_avo"){
        main_window.draw(SpriteLoader::baby_avo_normal_sprite);
    }else if(user_pet=="adult_ghost"){
        main_window.draw(SpriteLoader::adult_ghost_normal_sprite);
    }else{
        main_window.draw(SpriteLoader::baby_ghost_normal_sprite);
    }
    main_window.display();
  }
  return 0;
}