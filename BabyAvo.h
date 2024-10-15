// BabyAvo.h
#ifndef BABY_AVO_H
#define BABY_AVO_H

#include "Pet.h"
#include <iostream>

class BabyAvo : public Pet {
public:
    void make_sound() override {
        std::cout << "Baby Avo: Cheep!" << std::endl;
    }

    void display(sf::RenderWindow& window) override {
        // Implementation for displaying BabyAvo
    }

    void maxSleep() override {
        // Implement logic to maximize sleep for BabyAvo
    }

    void maxHealth() override {
        // Implement logic to maximize health for BabyAvo
    }

    void maxHunger() override {
        // Implement logic to maximize hunger for BabyAvo
    }
};

#endif // BABY_AVO_H
