#include"mini_game.h"
//initialising window
void mini_game::initialise_window(){
    game_video_mode.height=1080;
    game_video_mode.width=1920;
    game_window= new sf::RenderWindow(game_video_mode, "PetPal", sf::Style::Titlebar | sf::Style::Close);
    game_window->setFramerateLimit(60);
}


void mini_game::initialise_variables(){
    //initialising the variables
    game_window=nullptr;
    min_height_boxes=50.f;
    max_height_boxes=200.f;
    maximum_boxes=150;
    box_spawn_timer_max=10.f;
    box_spawn_timer=box_spawn_timer_max;
    
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
    float random_height_boxes=min_height_boxes + static_cast<float>(std::rand()) / RAND_MAX * (max_height_boxes - min_height_boxes); //to calculate random height
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
    render_boxes(*game_window);
    game_window->display();
}

void mini_game::spawn_boxes(){
    //spawns boxes and set their colors and positions 
    
    falling_boxes.setPosition(
      static_cast<float>(rand() % static_cast<int>(game_window->getSize().x -falling_boxes.getSize().x)),0.0);
    falling_boxes.setFillColor(sf::Color(0,0,128));
    boxes.push_back(falling_boxes);
}

 void mini_game::render_boxes(sf::RenderTarget& target){
    for(auto& i : boxes){
        target.draw(i);
    }
 }

 void mini_game::update(){
    poll_events();
    update_boxes();
 }

 void mini_game::update_boxes(){
    if(boxes.size()<maximum_boxes){
        if(box_spawn_timer>= box_spawn_timer_max){
            spawn_boxes();
            box_spawn_timer=0.f;
    }
    else{
        box_spawn_timer+=1.f;
    }
    }

    for(auto& e: boxes){
        e.move(0.f, 0.5f);
    }
    
 }