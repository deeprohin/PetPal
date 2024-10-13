#ifndef AVO_H
#define AVO_H

#include "pet_stats.h"
#include "quotesFile.h"

class avo:public PetStats{
public:
    avo(){
    avocado_quotes = {
        "What did the avocado say to the toast? You’re my butter half!",
        "If life gives you avocados, make guacamole!",
        "I’m just an avocado, living in a toast world.",
        "I’m not a regular avocado, I’m a cool avocado.",
        "You guac my world!",
        "An avocado a day keeps the bad vibes away.",
        "How does an avocado propose? With a guac ring!",
        "Just avocado-ing with the flow!"};
        avo_sound.openFromFile("Cute squish squish Sound Effect.mp3");
        avo_sound.setVolume(100);
    }
    std::vector<std::string> avocado_quotes;
    sf::Music avo_sound;
    void make_sound() override{
        if (avo_sound.getStatus() != sf::Sound::Playing) {
            avo_sound.play();
        }
    }

};
#endif