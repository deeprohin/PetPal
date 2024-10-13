#ifndef GHOST_H
#define GHOST_H

#include "pet_stats.h"
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>  // for std::time

class ghost : public PetStats {
private:
    std::vector<std::string> quotes; // Store ghost quotes
    sf::Music ghost_sound; // Sound specific to the Ghost

public:
    // Constructor to initialize quotes and load sound
    ghost() {
        quotes = {
            "I don’t mean to scare you, but I am just here for the boos!",
            "Ghosts are just like us—constantly looking for a good haunt!",
            "If you think I'm scary now, you should see me before my coffee!",
            "What do you call a ghost that tells jokes? A pun-derworld spirit!",
            "Boo! Just kidding. I’m just here for the snacks.",
            "Why don't ghosts like rain? Because it dampens their spirits!"
        };

        // Seed for random quote generation
        std::srand(static_cast<unsigned>(std::time(0)));

        // Load ghost sound file
        if (!ghost_sound.openFromFile("[Cartoon Sound FX] Ghost hover vintage synth effect.mp3")) {
            std::cout << "Failed to load ghost sound!" << std::endl;
        }
        ghost_sound.setVolume(100); // Set the volume
    }

    // Function to get a random quote
    std::string getRandomQuote() {
        int index = std::rand() % quotes.size();
        return quotes[index];
    }

    // Function to play ghost sound
    void make_sound() override {
        if (ghost_sound.getStatus() != sf::SoundSource::Playing) {
            ghost_sound.play();  // Play sound if not already playing
        }
    }
};

#endif  // GHOST_H