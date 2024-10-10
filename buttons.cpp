#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "MATHGAME.h"
#include "Animation.h"
#include"mini_game.h"
#include "adult_avo.h"
#include "baby_avo.h"
#include "adult_ghost.h"
#include "baby_ghost.h"
#include"pet_stats.h"

int main(){
    sf::Font font;
if (!font.loadFromFile("Regular.ttf")) {
    std::cout << "Font Not Found" << std::endl;
    return -1;
}
    //determining character type to determine which animation to laod in
    std::string user_pet;
    std::cin>>user_pet;
    PetStats petStats;


    //creating main window
    sf::RenderWindow main_window(sf::VideoMode(1920,1080), "My Virtual Pet");
    main_window.setFramerateLimit(60);
    sf::RectangleShape line(sf::Vector2f(1920, 5)); 
    line.setFillColor(sf::Color::Black); 
    line.setPosition(0, 120);
    
    //creating buttons
    sf::Texture sleeping_button_texture;
    if (!sleeping_button_texture.loadFromFile("moon.png")) {
        //change file path depending on machine, attribution: <a href="https://www.flaticon.com/free-icons/sleep" title="sleep icons">Sleep icons created by Good Ware - Flaticon</a> 
        std::cout << "Image Not Found" << std::endl;
        return -1;
    }
    sf::Sprite sleeping_button_sprite;
    sleeping_button_sprite.setTexture(sleeping_button_texture);
    sleeping_button_sprite.setPosition(40,130);

    sf::Texture shower_button_texture;
    if (!shower_button_texture.loadFromFile("shower (1).png")) {
        //change file path depending on machine, attribution:<a href="https://www.flaticon.com/free-icons/shower-head" title="shower head icons">Shower head icons created by Vitaly Gorbachev - Flaticon</a>
        std::cout << "Image Not Found" << std::endl;
        return -1;
    }
    sf::Sprite shower_button_sprite;
    shower_button_sprite.setTexture(shower_button_texture);
    shower_button_sprite.setPosition(470,130);

    sf::Texture game_button_texture;
    if (!game_button_texture.loadFromFile("console.png")) {
        //change file path depending on machine, attribution:<a href="https://www.flaticon.com/free-icons/joystick" title="joystick icons">Joystick icons created by Good Ware - Flaticon</a>
        std::cout << "Image Not Found" << std::endl;
        return -1;
    }
    sf::Sprite game_button_sprite;
    game_button_sprite.setTexture(game_button_texture);
    game_button_sprite.setPosition(900,130);

    sf::Texture food_button_texture;
    if (!food_button_texture.loadFromFile("cutlery.png")) {
        //change file path depending on machine, attribution:<a href="https://www.flaticon.com/free-icons/restaurant" title="restaurant icons">Restaurant icons created by Freepik - Flaticon</a>
        std::cout << "Image Not Found" << std::endl;
        return -1;
    }
    sf::Sprite food_button_sprite;
    food_button_sprite.setTexture(food_button_texture);
    food_button_sprite.setPosition(1310,130);

    sf::Texture health_button_texture;
    if (!health_button_texture.loadFromFile("first-aid-kit.png")) {
        //change file path depending on machine, attribution:<a href="https://www.flaticon.com/free-icons/health" title="health icons">Health icons created by Good Ware - Flaticon</a>
        return -1;
    }
    sf::Sprite health_button_sprite;
    health_button_sprite.setTexture(health_button_texture);
    health_button_sprite.setPosition(40,680);

    sf::Texture shopping_button_texture;
    if (!shopping_button_texture.loadFromFile("grocery-cart.png")) {
        //change file path depending on machine, attribution:<a href="https://www.flaticon.com/free-icons/supermarket" title="supermarket icons">Supermarket icons created by Freepik - Flaticon</a>
        return -1;
    }
    sf::Sprite shopping_button_sprite;
    shopping_button_sprite.setTexture(shopping_button_texture);
    shopping_button_sprite.setPosition(470,680);

    sf::Texture info_button_texture;
    if (!info_button_texture.loadFromFile("info.png")) {
        //change file path depending on machine, attribution:<a href="https://www.flaticon.com/free-icons/info" title="info icons">Info icons created by Stockio - Flaticon</a>
    }
    sf::Sprite info_button_sprite;
    info_button_sprite.setTexture(info_button_texture);
    info_button_sprite.setPosition(1310,680);

     sf::Texture math_button_texture;
    if (!math_button_texture.loadFromFile("math.png")) {
        //change file path depending on machine, attribution:<a href="https://www.flaticon.com/free-icons/math" title="math icons">Math icons created by Freepik - Flaticon</a>
    }
    sf::Sprite math_button_sprite;
    math_button_sprite.setTexture(math_button_texture);
    math_button_sprite.setPosition(900,680);
    //main loop of game
    while (main_window.isOpen()){
        sf::Event event;
        petStats.updateStats();
        while (main_window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                main_window.close();
                return 0;
            }
             
            //checking if user clicked the icon
            if(event.type == sf::Event::MouseButtonPressed){
                sf::Vector2i click_position=sf::Mouse::getPosition(main_window);
                int x=click_position.x;
                int y=click_position.y;
                if(x>=40&&x<=190&&y>=130&&y<=280){
                    std::cout<<"Sleeping Button"<<std::endl;
                    petStats.maxSleep();
                    if(user_pet=="adult_avo"){
                        adult_avo sleeping("Big2/sleeping/spritesheet.png", 0.8f, 8.0f, 8.0f);
                        sleeping.startAnimation_sleeping();
                        sf::Clock clock; // Clock to track time
                        sf::Clock total_animation_time;
                        while (main_window.isOpen()){   
                            sf::Event event;
                            while (main_window.pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed)
                                    main_window.close();
                            }

                            // Get the time elapsed since the last frame
                            float deltaTime = clock.restart().asSeconds();

                            // Update the Sleeping Sleeping
                            sleeping.update_sleeping(deltaTime);

                            

                            // Clear the window
                            main_window.clear(sf::Color(245, 245, 220)); // Optionally change the color for better visibility

                            // Draw the Sleeping sprite
                            sleeping.draw_sleeping(main_window);
                            main_window.draw(line);
                            main_window.draw(sleeping_button_sprite);
                            main_window.draw(shower_button_sprite);
                            main_window.draw(game_button_sprite);
                            main_window.draw(food_button_sprite);
                            main_window.draw(health_button_sprite);
                            main_window.draw(shopping_button_sprite);
                            main_window.draw(info_button_sprite);
                            main_window.draw(math_button_sprite);
                            petStats.renderStats(main_window, font);
                            // Display the window contents
                            
                            main_window.display();
                            if(total_animation_time.getElapsedTime().asSeconds()>=6){
                                break;
                            }
                        }
                    }else if(user_pet=="baby_avo"){
                        baby_avo sleeping("Small2/Sleeping/spritesheet.png", 0.8f, 8.0f, 8.0f);
                        sleeping.startAnimation_sleeping();
                        sf::Clock clock; // Clock to track time
                        sf::Clock total_animation_time;
                        while (main_window.isOpen()){   
                            sf::Event event;
                            while (main_window.pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed)
                                    main_window.close();
                            }

                            // Get the time elapsed since the last frame
                            float deltaTime = clock.restart().asSeconds();

                            // Update the Sleeping Sleeping
                            sleeping.update_sleeping(deltaTime);

                            // Clear the window
                            main_window.clear(sf::Color(245, 245, 220)); // Optionally change the color for better visibility

                            // Draw the Sleeping sprite
                            sleeping.draw_sleeping(main_window);
                            main_window.draw(line);
                            main_window.draw(sleeping_button_sprite);
                            main_window.draw(shower_button_sprite);
                            main_window.draw(game_button_sprite);
                            main_window.draw(food_button_sprite);
                            main_window.draw(health_button_sprite);
                            main_window.draw(shopping_button_sprite);
                            main_window.draw(info_button_sprite);
                            main_window.draw(math_button_sprite);
                            petStats.renderStats(main_window, font);
                            // Display the window contents
                            main_window.display();
                            if(total_animation_time.getElapsedTime().asSeconds()>=6){
                                break;
                            }
                        } 
                    }else if(user_pet=="adult_ghost"){
                        adult_ghost sleeping("Big/Sleeping.png", 0.8f, 8.0f, 8.0f);
                        sleeping.startAnimation_sleeping();
                        sf::Clock clock; // Clock to track time
                        sf::Clock total_animation_time;
                        while (main_window.isOpen()){   
                            sf::Event event;
                            while (main_window.pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed)
                                    main_window.close();
                            }

                            // Get the time elapsed since the last frame
                            float deltaTime = clock.restart().asSeconds();

                            // Update the Sleeping Sleeping
                            sleeping.update_sleeping(deltaTime);
                            
                            // Clear the window
                            main_window.clear(sf::Color(245, 245, 220)); // Optionally change the color for better visibility

                            // Draw the Sleeping sprite
                            sleeping.draw_sleeping(main_window);
                            main_window.draw(line);
                            main_window.draw(sleeping_button_sprite);
                            main_window.draw(shower_button_sprite);
                            main_window.draw(game_button_sprite);
                            main_window.draw(food_button_sprite);
                            main_window.draw(health_button_sprite);
                            main_window.draw(shopping_button_sprite);
                            main_window.draw(info_button_sprite);
                            main_window.draw(math_button_sprite);
                            petStats.renderStats(main_window, font);
                           

                           
                            // Display the window contents
                            main_window.display();
                            if(total_animation_time.getElapsedTime().asSeconds()>=6){
                                break;
                            }
                        } 
                    }else if(user_pet=="baby_ghost"){
                        baby_ghost sleeping("Small/Sleeping.png", 0.8f, 8.0f, 8.0f);
                        sleeping.startAnimation_sleeping();
                        sf::Clock clock; // Clock to track time
                        sf::Clock total_animation_time;
                        while (main_window.isOpen()){ 
                            sf::Event event;
                            while (main_window.pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed)
                                    main_window.close();
                            }

                            // Get the time elapsed since the last frame
                            float deltaTime = clock.restart().asSeconds();

                            // Update the Sleeping Sleeping
                            sleeping.update_sleeping(deltaTime);
                          
                            // Clear the window
                            main_window.clear(sf::Color(245, 245, 220)); // Optionally change the color for better visibility

                            // Draw the Sleeping sprite
                            sleeping.draw_sleeping(main_window);
                            main_window.draw(line);
                            main_window.draw(sleeping_button_sprite);
                            main_window.draw(shower_button_sprite);
                            main_window.draw(game_button_sprite);
                            main_window.draw(food_button_sprite);
                            main_window.draw(health_button_sprite);
                            main_window.draw(shopping_button_sprite);
                            main_window.draw(info_button_sprite);
                            main_window.draw(math_button_sprite);
                            petStats.renderStats(main_window, font);
                            // Display the window contents
                            main_window.display();
                            if(total_animation_time.getElapsedTime().asSeconds()>=6){
                                break;
                            }
                        }  
                    }
                }else if(x>=470&&x<=620&&y>=130&&y<=280){
                    std::cout<<"showering Button"<<std::endl;
                    petStats.maxHealth();
                    if(user_pet=="adult_avo"){
                        adult_avo test("Big2/showering/spritesheet.png", 1.4f, 8.0f, 8.0f);
                        test.startAnimation_shower();
                        sf::Clock clock; // Clock to track time
                        sf::Clock total_animation_time;
                        while (main_window.isOpen()){
                            sf::Event event;
                            while (main_window.pollEvent(event)) {
                                if (event.type == sf::Event::Closed){
                                    main_window.close();
                                }
                            }
                            // Get the time elapsed since the last frame
                            float deltaTime = clock.restart().asSeconds();
                            test.update_shower(deltaTime);
                            // Draw the shower
                            main_window.clear(sf::Color(245, 245, 220));
                            test.draw_shower(main_window);
                            main_window.draw(line);
                            main_window.draw(sleeping_button_sprite);
                            main_window.draw(shower_button_sprite);
                            main_window.draw(game_button_sprite);
                            main_window.draw(food_button_sprite);
                            main_window.draw(health_button_sprite);
                            main_window.draw(shopping_button_sprite);
                            main_window.draw(info_button_sprite);
                            main_window.draw(math_button_sprite);
                            petStats.renderStats(main_window, font);

                            // Display the window contents
                            main_window.display();
                            if(total_animation_time.getElapsedTime().asSeconds()>=6){
                                break;
                            }
                    }
                    }else if(user_pet=="baby_avo"){
                        baby_avo baby_showering("Small2/Showering/spritesheet.png", 0.8f, 8.0f, 8.0f);
                        baby_showering.startAnimation_shower();
                        sf::Clock clock; // Clock to track time
                        sf::Clock total_animation_time;
                        while (main_window.isOpen()){   
                           sf::Event event;
                            while (main_window.pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed)
                                    main_window.close();
                            }

                            // Get the time elapsed since the last frame
                            float deltaTime = clock.restart().asSeconds();
                            // Update the Sleeping Sleeping
                            baby_showering.update_shower(deltaTime);
                            // Clear the window
                            main_window.clear(sf::Color(245, 245, 220)); // Optionally change the color for better visibility

                            // Draw the Sleeping sprite
                            baby_showering.draw_shower(main_window);
                            main_window.draw(line);
                            main_window.draw(sleeping_button_sprite);
                            main_window.draw(shower_button_sprite);
                            main_window.draw(game_button_sprite);
                            main_window.draw(food_button_sprite);
                            main_window.draw(health_button_sprite);
                            main_window.draw(shopping_button_sprite);
                            main_window.draw(info_button_sprite);
                            main_window.draw(math_button_sprite);
                            petStats.renderStats(main_window, font);
                            // Display the window contents
                            main_window.display();
                            if(total_animation_time.getElapsedTime().asSeconds()>=6){
                                break;
                            }
                        }
                    }else if(user_pet=="adult_ghost"){
                        adult_ghost adult_ghost_showering("Big/Shower.png", 0.8f, 8.0f, 8.0f);
                        adult_ghost_showering.startAnimation_shower();
                        sf::Clock clock; // Clock to track time
                        sf::Clock total_animation_time;
                        while (main_window.isOpen()){   
                           sf::Event event;
                            while (main_window.pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed)
                                    main_window.close();
                            }

                            // Get the time elapsed since the last frame
                            float deltaTime = clock.restart().asSeconds();
                            // Update the Sleeping Sleeping
                            adult_ghost_showering.update_shower(deltaTime);
                            // Clear the window
                            main_window.clear(sf::Color(245, 245, 220)); // Optionally change the color for better visibility

                            // Draw the Sleeping sprite
                            adult_ghost_showering.draw_shower(main_window);
                            main_window.draw(line);
                            main_window.draw(sleeping_button_sprite);
                            main_window.draw(shower_button_sprite);
                            main_window.draw(game_button_sprite);
                            main_window.draw(food_button_sprite);
                            main_window.draw(health_button_sprite);
                            main_window.draw(shopping_button_sprite);
                            main_window.draw(info_button_sprite);
                            main_window.draw(math_button_sprite);
                            petStats.renderStats(main_window, font);
                            // Display the window contents
                            main_window.display();
                            if(total_animation_time.getElapsedTime().asSeconds()>=6){
                                break;
                            }
                        }
                    }else if(user_pet=="baby_ghost"){
                        baby_ghost adult_ghost_showering("Small/Shower.png", 0.8f, 8.0f, 8.0f);
                        adult_ghost_showering.startAnimation_shower();
                        sf::Clock clock; // Clock to track time
                        sf::Clock total_animation_time;
                        while (main_window.isOpen()){   
                           sf::Event event;
                            while (main_window.pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed)
                                    main_window.close();
                            }

                            // Get the time elapsed since the last frame
                            float deltaTime = clock.restart().asSeconds();
                            // Update the Sleeping Sleeping
                            adult_ghost_showering.update_shower(deltaTime);
                            // Clear the window
                            main_window.clear(sf::Color(245, 245, 220)); // Optionally change the color for better visibility

                            // Draw the Sleeping sprite
                            adult_ghost_showering.draw_shower(main_window);
                            main_window.draw(line);
                            main_window.draw(sleeping_button_sprite);
                            main_window.draw(shower_button_sprite);
                            main_window.draw(game_button_sprite);
                            main_window.draw(food_button_sprite);
                            main_window.draw(health_button_sprite);
                            main_window.draw(shopping_button_sprite);
                            main_window.draw(info_button_sprite);
                            main_window.draw(math_button_sprite);
                            petStats.renderStats(main_window, font);
                            // Display the window contents
                            main_window.display();
                            if(total_animation_time.getElapsedTime().asSeconds()>=6){
                                break;
                            }
                        }
                    }
                }else if(x>=900&&x<=1050&&y>=130&&y<=280){
                    std::cout<<"Game Button"<<std::endl;
                    mini_game new_game;
                    while(new_game.window_open()){
                        new_game.update();
                        new_game.render();
                    }
                    petStats.changeMoney(new_game.money_earned_end());

                }else if(x>=1310&&x<=1460&&y>=130&&y<=280){
                    std::cout<<"Eating Button"<<std::endl;
                    petStats.maxHunger();
                    if(user_pet=="adult_avo"){
                        adult_avo adult_avo_eating("Big2/Eating/spritesheet.png", 1.4f, 8.0f, 8.0f);
                        adult_avo_eating.startAnimation_eating();
                        sf::Clock clock1; // Clock to track time
                        sf::Clock total_animation_time1;
                        while (main_window.isOpen()){
                            sf::Event event;
                            while (main_window.pollEvent(event)) {
                                if (event.type == sf::Event::Closed){
                                    main_window.close();
                                }
                            }
                            // Get the time elapsed since the last frame
                            float deltaTime = clock1.restart().asSeconds();
                            adult_avo_eating.update_eating(deltaTime);
                        
                            // Draw the shower
                            main_window.clear(sf::Color(245, 245, 220));
                            adult_avo_eating.draw_eating(main_window);
                            main_window.draw(line);
                            main_window.draw(sleeping_button_sprite);
                            main_window.draw(shower_button_sprite);
                            main_window.draw(game_button_sprite);
                            main_window.draw(food_button_sprite);
                            main_window.draw(health_button_sprite);
                            main_window.draw(shopping_button_sprite);
                            main_window.draw(info_button_sprite);
                            main_window.draw(math_button_sprite);
                            petStats.renderStats(main_window, font);

                            // Display the window contents
                            main_window.display();
                            if(total_animation_time1.getElapsedTime().asSeconds()>=6){
                                break;
                            }
                    }
                    }else if(user_pet=="baby_avo"){
                        baby_avo eating("Small2/Eating/spritesheet.png", 1.4f, 8.0f, 8.0f);
                        eating.startAnimation_eating();
                        sf::Clock clock1; // Clock to track time
                        sf::Clock total_animation_time1;
                        while (main_window.isOpen()){
                             sf::Event event;
                            while (main_window.pollEvent(event)) {
                                if (event.type == sf::Event::Closed){
                                    main_window.close();
                                }
                            }
                            // Get the time elapsed since the last frame
                            float deltaTime = clock1.restart().asSeconds();
                            eating.update_eating(deltaTime);
                        
                            // Draw the shower
                            main_window.clear(sf::Color(245, 245, 220));
                            eating.draw_eating(main_window);
                            main_window.draw(line);
                            main_window.draw(sleeping_button_sprite);
                            main_window.draw(shower_button_sprite);
                            main_window.draw(game_button_sprite);
                            main_window.draw(food_button_sprite);
                            main_window.draw(health_button_sprite);
                            main_window.draw(shopping_button_sprite);
                            main_window.draw(info_button_sprite);
                            main_window.draw(math_button_sprite);
                            petStats.renderStats(main_window, font);

                            // Display the window contents
                            main_window.display();
                            if(total_animation_time1.getElapsedTime().asSeconds()>=6){
                                break;
                            }
                        }
                    }else if(user_pet=="adult_ghost"){
                        adult_ghost eating("Big/eating.png", 1.4f, 8.0f, 8.0f);
                        eating.startAnimation_eating();
                        sf::Clock clock1; // Clock to track time
                        sf::Clock total_animation_time1;
                        while (main_window.isOpen()){
                             sf::Event event;
                            while (main_window.pollEvent(event)) {
                                if (event.type == sf::Event::Closed){
                                    main_window.close();
                                }
                            }
                            // Get the time elapsed since the last frame
                            float deltaTime = clock1.restart().asSeconds();
                            eating.update_eating(deltaTime);
                        
                            // Draw the shower
                            main_window.clear(sf::Color(245, 245, 220));
                            eating.draw_eating(main_window);
                            main_window.draw(line);
                            main_window.draw(sleeping_button_sprite);
                            main_window.draw(shower_button_sprite);
                            main_window.draw(game_button_sprite);
                            main_window.draw(food_button_sprite);
                            main_window.draw(health_button_sprite);
                            main_window.draw(shopping_button_sprite);
                            main_window.draw(info_button_sprite);
                            main_window.draw(math_button_sprite);
                            petStats.renderStats(main_window, font);

                            // Display the window contents
                            main_window.display();
                            if(total_animation_time1.getElapsedTime().asSeconds()>=6){
                                break;
                            }
                        }
                    }else if(user_pet=="baby_ghost"){
                        baby_ghost eating("Small/eating.png", 1.4f, 8.0f, 8.0f);
                        eating.startAnimation_eating();
                        sf::Clock clock1; // Clock to track time
                        sf::Clock total_animation_time1;
                        while (main_window.isOpen()){
                             sf::Event event;
                            while (main_window.pollEvent(event)) {
                                if (event.type == sf::Event::Closed){
                                    main_window.close();
                                }
                            }
                            // Get the time elapsed since the last frame
                            float deltaTime = clock1.restart().asSeconds();
                            eating.update_eating(deltaTime);
                        
                            // Draw the shower
                            main_window.clear(sf::Color(245, 245, 220));
                            eating.draw_eating(main_window);
                            main_window.draw(line);
                            main_window.draw(sleeping_button_sprite);
                            main_window.draw(shower_button_sprite);
                            main_window.draw(game_button_sprite);
                            main_window.draw(food_button_sprite);
                            main_window.draw(health_button_sprite);
                            main_window.draw(shopping_button_sprite);
                            main_window.draw(info_button_sprite);
                            main_window.draw(math_button_sprite);
                            petStats.renderStats(main_window, font);

                            // Display the window contents
                            main_window.display();
                            if(total_animation_time1.getElapsedTime().asSeconds()>=6){
                                break;
                            }
                        }
                    }
                }else if(x>=40&&x<=190&&y>=680&&y<=830){
                    std::cout<<"Medicine Button"<<std::endl;
                    petStats.maxHealth();
                    if(user_pet=="adult_avo"){
                        adult_avo adult_avo_meds("New Piskel-1 10.15.48ΓÇ»PM.png (2).png", 1.4f, 8.0f, 8.0f);
                        adult_avo_meds.startAnimation_medicine();
                        sf::Clock clock1; // Clock to track time
                        sf::Clock total_animation_time1;
                        while (main_window.isOpen()){
                            sf::Event event;
                            while (main_window.pollEvent(event)) {
                                if (event.type == sf::Event::Closed){
                                    main_window.close();
                                }
                            }
                            // Get the time elapsed since the last frame
                            float deltaTime = clock1.restart().asSeconds();
                            adult_avo_meds.update_medicine(deltaTime);
                            // Draw the shower
                            main_window.clear(sf::Color(245, 245, 220));
                            adult_avo_meds.draw_medicine(main_window);
                            main_window.draw(line);
                            main_window.draw(sleeping_button_sprite);
                            main_window.draw(shower_button_sprite);
                            main_window.draw(game_button_sprite);
                            main_window.draw(food_button_sprite);
                            main_window.draw(health_button_sprite);
                            main_window.draw(shopping_button_sprite);
                            main_window.draw(info_button_sprite);
                            main_window.draw(math_button_sprite);
                            petStats.renderStats(main_window, font);

                            // Display the window contents
                            main_window.display();
                            if(total_animation_time1.getElapsedTime().asSeconds()>=6){
                                break;
                            }
                    }
                    }else if(user_pet=="baby_avo"){
                        baby_avo meds("Small2/medications/spritesheet.png", 1.4f, 8.0f, 8.0f);
                        meds.startAnimation_medicine();
                        sf::Clock clock1; // Clock to track time
                        sf::Clock total_animation_time1;
                        while (main_window.isOpen()){
                            sf::Event event;
                            while (main_window.pollEvent(event)) {
                                if (event.type == sf::Event::Closed){
                                    main_window.close();
                                }
                            }
                            // Get the time elapsed since the last frame
                            float deltaTime = clock1.restart().asSeconds();
                            meds.update_medicine(deltaTime);
                            // Draw the shower
                            main_window.clear(sf::Color(245, 245, 220));
                            meds.draw_medicine(main_window);
                            main_window.draw(line);
                            main_window.draw(sleeping_button_sprite);
                            main_window.draw(shower_button_sprite);
                            main_window.draw(game_button_sprite);
                            main_window.draw(food_button_sprite);
                            main_window.draw(health_button_sprite);
                            main_window.draw(shopping_button_sprite);
                            main_window.draw(info_button_sprite);
                            main_window.draw(math_button_sprite);
                            petStats.renderStats(main_window, font);

                            // Display the window contents
                            main_window.display();
                            if(total_animation_time1.getElapsedTime().asSeconds()>=6){
                                break;
                            }

                        }
                    }else if(user_pet=="adult_ghost"){
                        adult_ghost meds("Big/Medicine .png", 1.4f, 8.0f, 8.0f);
                        meds.startAnimation_medicine();
                        sf::Clock clock1; // Clock to track time
                        sf::Clock total_animation_time1;
                        while (main_window.isOpen()){
                            sf::Event event;
                            while (main_window.pollEvent(event)) {
                                if (event.type == sf::Event::Closed){
                                    main_window.close();
                                }
                            }
                            // Get the time elapsed since the last frame
                            float deltaTime = clock1.restart().asSeconds();
                            meds.update_medicine(deltaTime);
                            // Draw the shower
                            main_window.clear(sf::Color(245, 245, 220));
                            meds.draw_medicine(main_window);
                            main_window.draw(line);
                            main_window.draw(sleeping_button_sprite);
                            main_window.draw(shower_button_sprite);
                            main_window.draw(game_button_sprite);
                            main_window.draw(food_button_sprite);
                            main_window.draw(health_button_sprite);
                            main_window.draw(shopping_button_sprite);
                            main_window.draw(info_button_sprite);
                            main_window.draw(math_button_sprite);
                            petStats.renderStats(main_window, font);

                            // Display the window contents
                            main_window.display();
                            if(total_animation_time1.getElapsedTime().asSeconds()>=6){
                                break;
                            }

                        }
                    }else if(user_pet=="baby_ghost"){
                        baby_ghost meds("Small/Medicine .png", 1.4f, 8.0f, 8.0f);
                        meds.startAnimation_medicine();
                        sf::Clock clock1; // Clock to track time
                        sf::Clock total_animation_time1;
                        while (main_window.isOpen()){
                            sf::Event event;
                            while (main_window.pollEvent(event)) {
                                if (event.type == sf::Event::Closed){
                                    main_window.close();
                                }
                            }
                            // Get the time elapsed since the last frame
                            float deltaTime = clock1.restart().asSeconds();
                            meds.update_medicine(deltaTime);
                            // Draw the shower
                            main_window.clear(sf::Color(245, 245, 220));
                            meds.draw_medicine(main_window);
                            main_window.draw(line);
                            main_window.draw(sleeping_button_sprite);
                            main_window.draw(shower_button_sprite);
                            main_window.draw(game_button_sprite);
                            main_window.draw(food_button_sprite);
                            main_window.draw(health_button_sprite);
                            main_window.draw(shopping_button_sprite);
                            main_window.draw(info_button_sprite);
                            main_window.draw(math_button_sprite);
                            petStats.renderStats(main_window, font);

                            // Display the window contents
                            main_window.display();
                            if(total_animation_time1.getElapsedTime().asSeconds()>=6){
                                break;
                            }
                        }

                        }
                }else if(x>=470&&x<=620&&y>=680&&y<=830){
                    std::cout<<"Shopping Button"<<std::endl;
                }else if(x>=900&&x<=1050&&y>=680&&y<=830){
                    std::cout<<"Math Button"<<std::endl;
                    math_game test;
                }else if(x>=1310&&x<=1460&&y>=680&&y<=830){
                    std::cout<<"Info Button"<<std::endl;
                }
            }    
        }
        main_window.clear(sf::Color(245, 245, 220));
        main_window.draw(line);
        main_window.draw(sleeping_button_sprite);
        main_window.draw(shower_button_sprite);
        main_window.draw(game_button_sprite);
        main_window.draw(food_button_sprite);
        main_window.draw(health_button_sprite);
        main_window.draw(shopping_button_sprite);
        main_window.draw(info_button_sprite);
        main_window.draw(math_button_sprite);
        petStats.renderStats(main_window,font);
        main_window.display();
    }
    return 0; 
}