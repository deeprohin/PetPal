#ifndef MATHGAME_H
#define MATHGAME_H

#include<iostream>
#include <cstdlib> 
#include <ctime> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Animation.h"

class math_game{
    private:
        sf::RenderWindow* game_window;
        sf::Event ev;
        int correct_answers;

        //store current question and answer: 
        std::string current_question;
        int current_answer;
        std::string current_input;
        int number_of_answers;
        int score;

        void generate_question();
        void display_intro();
        void rules_page();
        void display_results(); //display how many question they got correct and coins gained as a result

        //time keeping for clock
        sf::Clock timer; 
        double total_time;
        sf::Music math_audio;
    public:
        math_game();//constructor to initialize game window
        ~math_game();
        void run();
        void render();
};
#endif