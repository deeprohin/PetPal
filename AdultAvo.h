// AdultAvo.h
#ifndef ADULT_AVO_H
#define ADULT_AVO_H

#include "Pet.h"
#include <iostream>

class AdultAvo : public Pet {
public:
    void make_sound() override {
        std::cout << "Adult Avo: Chirp!" << std::endl;
    }

    void display(sf::RenderWindow& window) override {
        // Implementation for displaying AdultAvo
        // For example:
        // window.draw(sprite);
    }

    void maxSleep() override {
        // Implement logic to maximize sleep for AdultAvo
    }

    void maxHealth() override {
        // Implement logic to maximize health for AdultAvo
    }

    void maxHunger() override {
        // Implement logic to maximize hunger for AdultAvo
    }
};

#endif // ADULT_AVO_H
