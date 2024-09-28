#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib> //for random function
using namespace std;
class mini_game{
    private:
        sf::RenderWindow* game_window;
        sf::Event ev;
        sf::VideoMode game_video_mode;
        vector<sf::RectangleShape> boxes;
        sf::RectangleShape falling_boxes;

        //variables for boxes
        int maximum_boxes;//how many boxes can the game generate in total
        int boxes_one_time; //how many boxes on the screen at once
        float min_height_boxes;
        float max_height_boxes;
        float box_spawn_timer;
        float box_spawn_timer_max;

        //for the image
        sf::Texture mini_game_texture;

        //for the slider variable
        sf::RectangleShape slider_track;
        sf::Sprite slider_knob;
        bool is_dragging;

        //points
        bool game_over;
        
        //private functions
        void initialise_variables(); 
        void initialise_window();

    public:
        mini_game(); //comstructor
        ~mini_game(); //destructor
        void initialise_boxes();
        bool window_open();
        void render();
        void update();
        void poll_events();
        void spawn_boxes();
        void render_boxes(sf::RenderTarget& target);
        void update_boxes();
        void initialise_image();
        void initialise_slider();
        void update_slider();
};

