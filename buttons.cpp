#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main(){
    //creating main window
    sf::RenderWindow main_window(sf::VideoMode(1920,1080), "My Virtual Pet");
    sf::RectangleShape line(sf::Vector2f(1920, 5)); 
    line.setFillColor(sf::Color::Black); 
    line.setPosition(0, 120);

    //creating buttons
    sf::Texture sleeping_button_texture;
    if (!sleeping_button_texture.loadFromFile("/Users/phuchaduynguyen/Desktop/C++ Programming/oop project/Game Buttons/moon.png")) {
        //change file path depending on machine, attribution: <a href="https://www.flaticon.com/free-icons/sleep" title="sleep icons">Sleep icons created by Good Ware - Flaticon</a> 
        std::cout << "Image Not Found" << std::endl;
        return -1;
    }
    sf::Sprite sleeping_button_sprite;
    sleeping_button_sprite.setTexture(sleeping_button_texture);
    sleeping_button_sprite.setPosition(40,130);

    sf::Texture shower_button_texture;
    if (!shower_button_texture.loadFromFile("/Users/phuchaduynguyen/Desktop/C++ Programming/oop project/Game Buttons/shower (1).png")) {
        //change file path depending on machine, attribution:<a href="https://www.flaticon.com/free-icons/shower-head" title="shower head icons">Shower head icons created by Vitaly Gorbachev - Flaticon</a>
        std::cout << "Image Not Found" << std::endl;
        return -1;
    }
    sf::Sprite shower_button_sprite;
    shower_button_sprite.setTexture(shower_button_texture);
    shower_button_sprite.setPosition(470,130);

    sf::Texture game_button_texture;
    if (!game_button_texture.loadFromFile("/Users/phuchaduynguyen/Desktop/C++ Programming/oop project/Game Buttons/console.png")) {
        //change file path depending on machine, attribution:<a href="https://www.flaticon.com/free-icons/joystick" title="joystick icons">Joystick icons created by Good Ware - Flaticon</a>
        std::cout << "Image Not Found" << std::endl;
        return -1;
    }
    sf::Sprite game_button_sprite;
    game_button_sprite.setTexture(game_button_texture);
    game_button_sprite.setPosition(900,130);

    sf::Texture food_button_texture;
    if (!food_button_texture.loadFromFile("/Users/phuchaduynguyen/Desktop/C++ Programming/oop project/Game Buttons/cutlery.png")) {
        //change file path depending on machine, attribution:<a href="https://www.flaticon.com/free-icons/restaurant" title="restaurant icons">Restaurant icons created by Freepik - Flaticon</a>
        std::cout << "Image Not Found" << std::endl;
        return -1;
    }
    sf::Sprite food_button_sprite;
    food_button_sprite.setTexture(food_button_texture);
    food_button_sprite.setPosition(1310,130);

    sf::Texture health_button_texture;
    if (!health_button_texture.loadFromFile("/Users/phuchaduynguyen/Desktop/C++ Programming/oop project/Game Buttons/first-aid-kit.png")) {
        //change file path depending on machine, attribution:<a href="https://www.flaticon.com/free-icons/health" title="health icons">Health icons created by Good Ware - Flaticon</a>
        return -1;
    }
    sf::Sprite health_button_sprite;
    health_button_sprite.setTexture(health_button_texture);
    health_button_sprite.setPosition(40,680);

    sf::Texture shopping_button_texture;
    if (!shopping_button_texture.loadFromFile("/Users/phuchaduynguyen/Desktop/C++ Programming/oop project/Game Buttons/grocery-cart.png")) {
        //change file path depending on machine, attribution:<a href="https://www.flaticon.com/free-icons/supermarket" title="supermarket icons">Supermarket icons created by Freepik - Flaticon</a>
        return -1;
    }
    sf::Sprite shopping_button_sprite;
    shopping_button_sprite.setTexture(shopping_button_texture);
    shopping_button_sprite.setPosition(470,680);

    sf::Texture info_button_texture;
    if (!info_button_texture.loadFromFile("/Users/phuchaduynguyen/Desktop/C++ Programming/oop project/Game Buttons/info.png")) {
        //change file path depending on machine, attribution:<a href="https://www.flaticon.com/free-icons/info" title="info icons">Info icons created by Stockio - Flaticon</a>
    }
    sf::Sprite info_button_sprite;
    info_button_sprite.setTexture(info_button_texture);
    info_button_sprite.setPosition(1310,680);

     sf::Texture math_button_texture;
    if (!math_button_texture.loadFromFile("/Users/phuchaduynguyen/Desktop/C++ Programming/oop project/Game Buttons/math.png")) {
        //change file path depending on machine, attribution:<a href="https://www.flaticon.com/free-icons/math" title="math icons">Math icons created by Freepik - Flaticon</a>
    }
    sf::Sprite math_button_sprite;
    math_button_sprite.setTexture(math_button_texture);
    math_button_sprite.setPosition(900,680);
    //main loop of game
    while (main_window.isOpen()){
        sf::Event event;
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
                }else if(x>=470&&x<=620&&y>=130&&y<=280){
                    std::cout<<"showering Button"<<std::endl;
                }else if(x>=900&&x<=1050&&y>=130&&y<=280){
                    std::cout<<"Game Button"<<std::endl;
                }else if(x>=1310&&x<=1460&&y>=130&&y<=280){
                    std::cout<<"Eating Button"<<std::endl;
                }else if(x>=40&&x<=190&&y>=680&&y<=830){
                    std::cout<<"Medicine Button"<<std::endl;
                }else if(x>=470&&x<=620&&y>=680&&y<=830){
                    std::cout<<"Shopping Button"<<std::endl;
                }else if(x>=900&&x<=1050&&y>=680&&y<=830){
                    std::cout<<"Math Button"<<std::endl;
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
        main_window.display();
    }
    return 0; 
}