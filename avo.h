#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include "pet_stats.h"  // Ensure this header is included for PetStats

class avo : public PetStats {
private:
    std::vector<std::string> avocado_quotes; // Quotes should be defined here
    sf::Music avo_sound; // Changed from ghost_sound to avo_sound

public:
    // Constructor to initialize quotes and load sound
    avo() {
        // Initialize the quotes for Avocado
        avocado_quotes = {
            "What did the avocado say to the toast? You’re my butter half!",
            "If life gives you avocados, make guacamole!",
            "I’m just an avocado, living in a toast world.",
            "I’m not a regular avocado, I’m a cool avocado.",
            "You guac my world!",
            "An avocado a day keeps the bad vibes away.",
            "How does an avocado propose? With a guac ring!",
            "Just avocado-ing with the flow!"
        };

        // Function to load sound
        if (!avo_sound.openFromFile("[Cartoon Sound FX] Avocado sound effect.mp3")) {
            std::cout << "Failed to load avocado sound!" << std::endl;
        }
        avo_sound.setVolume(100); // Set the volume
    }

    // Function to make sound
    void make_sound() override {
        if (avo_sound.getStatus() != sf::Sound::Playing) {
            avo_sound.play();
        }
    }

    // Function to get a random quote for Avocado
    std::string getRandomAvoQuote() {
        std::srand(static_cast<unsigned>(std::time(0))); // Seed for random number generation
        int index = std::rand() % avocado_quotes.size();
        return avocado_quotes[index];
    }

    // Function to update the Avo quote
    void updateAvoQuote(std::string& selectedQuote, sf::Clock& quoteClock,
                        float quoteInterval, bool& quoteVisible) {
        if (quoteClock.getElapsedTime().asSeconds() >= quoteInterval) {
            selectedQuote = getRandomAvoQuote();
            quoteClock.restart();
            quoteVisible = true;
        }
float displayDuration = 10.0f;
        if (quoteVisible && quoteClock.getElapsedTime().asSeconds() >= displayDuration) {
            quoteVisible = false;
        }
    }
};