#ifndef GHOST_H
#define GHOST_H

#include "pet_stats.h"
#include "quotesFile.h"

class ghost:public PetStats{
public:
    ghost(){
    ghost_quotes = {
        "I don’t mean to scare you, but I am just here for the boos!",
        "Ghosts are just like us—constantly looking for a good haunt!",
        "If you think I'm scary now, you should see me before my coffee!",
        "What do you call a ghost that tells jokes? A pun-derworld spirit!",
        "Boo! Just kidding. I’m just here for the snacks.",
        "Why dont ghosts like rain? Because it dampens their spirits!"};
        ghost_sound.openFromFile("[Cartoon Sound FX] Ghost hover vintage synth effect.mp3");
        ghost_sound.setVolume(100);
    }
    std::vector<std::string> ghost_quotes;
    sf::Music ghost_sound;
    void make_sound() override{
         if (ghost_sound.getStatus() != sf::Sound::Playing) {
            ghost_sound.play();
        }
    }   
};
#endif