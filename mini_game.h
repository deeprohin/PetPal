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
        float box_spawn_timer;
        float min_height_boxes;
        float max_height_boxes;

        //private functions
        void initialise_variables(); 
        void initialise_window();

    public:
        mini_game(); //comstructor
        ~mini_game(); //destructor
        void initialise_boxes();
        bool window_open();
        void render();
        void poll_events();


};

