#include"mini_game.h"
//initialising window
void mini_game::initialise_window(){
    game_video_mode.height=1080;
    game_video_mode.width=1920;
    game_window= new sf::RenderWindow(game_video_mode, "PetPal", sf::Style::Titlebar | sf::Style::Close| sf::Style::Resize);
    game_window->setFramerateLimit(60);
}

void mini_game::initialise_image(){
    mini_game_texture.loadFromFile("/Users/deeprohin/Desktop/Programming/Sem 2/PetPal/character.jpg");
    slider_knob.setTexture(mini_game_texture);
    slider_knob.setScale(90.6f / mini_game_texture.getSize().x, (90.6f * static_cast<float>(mini_game_texture.getSize().y) / mini_game_texture.getSize().x) / mini_game_texture.getSize().y); // Scaling the image
    slider_knob.setPosition(810, 700);
}


void mini_game::initialise_variables(){
    //initialising the variables
    game_window=nullptr;
    min_height_boxes=50.f;
    max_height_boxes=200.f;
    maximum_boxes=100;
    box_spawn_timer_max=10.f;
    box_spawn_timer=box_spawn_timer_max;
    boxes_one_time=1;
    is_dragging=false;
    game_over=false;
    points=0;
}

mini_game::mini_game(){
    //constructor
    initialise_variables();
    initialise_window();
    initialise_boxes();
    initialise_image();
    initialise_slider();
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
            //to check for the dragging one i.e. if the mouse position is on the knob and is clicked upon it will set the is_dragging boolean to truew
            case (sf::Event::MouseButtonPressed):
                if(ev.mouseButton.button==sf::Mouse::Left){
                    if(slider_knob.getGlobalBounds().contains(ev.mouseButton.x,ev.mouseButton.y)){
                        is_dragging=true;
                    }
                }
                break;
            case(sf::Event::MouseButtonReleased):
                if(ev.mouseButton.button==sf::Mouse::Left){
                    is_dragging=false;
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
    game_window->draw(slider_track);
    game_window->draw(slider_knob);

    if(game_over){
        game_window->display();
        game_window->close();
        return;
    }

    game_window->display();
}

void mini_game::spawn_boxes(){
    //spawns boxes and set their colors and positions 
    float random_height_boxes=min_height_boxes + static_cast<float>(std::rand()) / RAND_MAX * (max_height_boxes - min_height_boxes); //to calculate random height
    falling_boxes.setSize(sf::Vector2f(50.f, random_height_boxes));
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
    update_slider();
    update_points();
 }

 void mini_game::update_boxes(){
    if(boxes.size()<boxes_one_time){
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
        //checking if the box has touch the slider
        if(e.getPosition().y+e.getSize().y >= slider_track.getPosition().y){
            game_over=true;
        }
    }

    //removing boxes that went out of the screen

 }
 
 void mini_game::initialise_slider(){
    slider_track.setSize(sf::Vector2f(sf::Vector2f(static_cast<float>(game_window->getSize().x),5.0f)));
    slider_track.setPosition(0, 762);
    slider_track.setFillColor(sf::Color::Black);

 }

 void mini_game::update_slider(){
    if(is_dragging){
        float position_of_mouse=static_cast<float>(sf::Mouse::getPosition(*game_window).x);
        float position_of_knob = position_of_mouse - (slider_knob.getGlobalBounds().width / 2);
        position_of_knob = std::max(slider_track.getPosition().x, std::min(position_of_knob,slider_track.getPosition().x + slider_track.getSize().x - slider_knob.getGlobalBounds().width));
        //setting the postiion of the slider knob
        slider_knob.setPosition(position_of_knob, slider_knob.getPosition().y);
    }
 }
 
 void mini_game::update_points(){
    for(int i=0; i<boxes.size(); i++){
        if (slider_knob.getGlobalBounds().intersects(boxes[i].getGlobalBounds())){
            points++; // Increase points
            boxes.erase(boxes.begin()+i);
            i--; //because we remove one box...from the vector we need to deccrease the iterating counter
            cout<<points<<endl;
        }
    }
    
 }