#include"mini_game.h"
//initialising window
void mini_game::initialise_window(){
    game_video_mode.height=1080;
    game_video_mode.width=1920;
    game_window= new sf::RenderWindow(game_video_mode, "PetPal", sf::Style::Titlebar | sf::Style::Close);
}


void mini_game::initialise_variables(){
    //initialising the variables
    game_window=nullptr;
    min_height_boxes=50.f;
    max_height_boxes=200.f;
    maximum_boxes=150;
    box_spawn_timer=10;
    boxes_one_time=5;

}

mini_game::mini_game(){
    //constructor
    initialise_variables();
    initialise_window();
    initialise_boxes();
}

mini_game::~mini_game(){
    //destructor
    delete game_window;
}


void mini_game::initialise_boxes(){
    //to initialise the boxes and setting the properties
    falling_boxes.setPosition(10.f,10.f); //setting position of the boxes to start from 10,10
    float random_height_boxes=min_height_boxes + static_cast<float>(std::rand()) / RAND_MAX / (max_height_boxes - min_height_boxes); //to calculate random height
    falling_boxes.setSize(sf::Vector2f(50.f, random_height_boxes));
    falling_boxes.setFillColor(sf::Color::Red);
    falling_boxes.setOutlineColor(sf::Color::White);
    falling_boxes.setOutlineThickness(1.f);
}

bool mini_game::window_open(){
    return game_window->isOpen();
}

void mini_game::poll_events(){
     //to do some actions depending upon what the user inputted
    while(game_window->pollEvent(ev)){
        switch(ev.type){
            case (sf::Event::Closed):
                game_window->close();
                break;
            case (sf::Event::KeyPressed):
                if(ev.key.code==sf::Keyboard::Escape){
                    game_window->close();
                }
                break;
            default:
                break;
        }
    }
}

void mini_game::render(){
    //draws and represents everything on the screen
    game_window->clear(sf::Color(230,230,220));
    game_window->draw(falling_boxes);
    game_window->display();
}