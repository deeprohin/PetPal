#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

#include "pet_stats.h"
// inheriting from the petStats class
class avo : public PetStats {
 private:
  std::vector<std::string> avocado_quotes;  // quotes
  sf::Music avo_sound;                      // avo sound

 public:
  // constructor to initialize quotes and load sound
  avo() {
    // initializing the quotes for Avocado
    avocado_quotes = {
        "What did the avocado say to the toast? You’re my butter half!",
        "If life gives you avocados, make guacamole!",
        "I’m just an avocado, living in a toast world.",
        "I’m not a regular avocado, I’m a cool avocado.",
        "You guac my world!",
        "An avocado a day keeps the bad vibes away.",
        "How does an avocado propose? With a guac ring!",
        "Just avocado-ing with the flow!"};

    // function to load sound
    if (!avo_sound.openFromFile(
            "[Cartoon Sound FX] Avocado sound effect.mp3")) {
      std::cout << "Failed to load avocado sound!" << std::endl;
    }
    avo_sound.setVolume(100);  // setting the volume
  }

  // function to make sound
  void make_sound() override {
    if (avo_sound.getStatus() != sf::Sound::Playing) {
      avo_sound.play();
    }
  }

  // function to get a random quote for the avocado
  std::string getRandomAvoQuote() {
    std::srand(static_cast<unsigned>(
        std::time(0)));  // seed for random number generation
    int index = std::rand() % avocado_quotes.size();
    return avocado_quotes[index];
  }

  // function to update the Avo quote
  void updateAvoQuote(std::string& selectedQuote, sf::Clock& quoteClock,
                      float quoteInterval, bool& quoteVisible) {
    if (quoteClock.getElapsedTime().asSeconds() >= quoteInterval) {
      selectedQuote = getRandomAvoQuote();
      quoteClock.restart();
      quoteVisible = true;
    }
    float displayDuration = 10.0f;
    if (quoteVisible &&
        quoteClock.getElapsedTime().asSeconds() >= displayDuration) {
      quoteVisible = false;
    }
  }
};