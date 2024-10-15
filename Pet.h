// Pet.h
#ifndef PET_H
#define PET_H

#include <SFML/Graphics.hpp>

class Pet {
public:
    virtual ~Pet() = default; // Virtual destructor for polymorphism

    // Common methods for all pets
    virtual void make_sound() = 0; // Pure virtual function
    virtual void display(sf::RenderWindow& window) = 0; // Pure virtual function
    virtual void maxSleep() = 0;    // Pure virtual function for maximizing sleep
    virtual void maxHealth() = 0;    // Pure virtual function for maximizing health
    virtual void maxHunger() = 0;    // Pure virtual function for maximizing hunger
};

#endif // PET_H
