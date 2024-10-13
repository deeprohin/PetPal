#ifndef MEDICINE_H
#define MEDICINE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Medicine {
public:
    Medicine(const std::string& spriteSheetPath, float frameDuration, float scaleX = 1.0f, float scaleY = 1.0f):frameDuration_medicine(frameDuration), elapsedTime_medicine(0.0f), currentFrame_medicine(0), isAnimating_medicine(false) {};

    virtual void startAnimation_medicine()=0;
    virtual void update_medicine(float deltaTime)=0;
    virtual void draw_medicine(sf::RenderWindow& window)=0;
    sf::Sprite sprite_medicine;
    sf::Texture texture_medicine;
    float frameDuration_medicine;
    int currentFrame_medicine;
    float elapsedTime_medicine;
    bool isAnimating_medicine;
    sf::Vector2f position_medicine;
    sf::Vector2f originalPosition_medicine;
    virtual void updateSpriteRect_medicine()=0;
};

#endif // MEDICINE_H
