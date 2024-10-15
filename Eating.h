#ifndef EATING_H
#define EATING_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Eating {
public:
    Eating(const std::string& spriteSheetPath, float frameDuration, float scaleX, float scaleY): frameDuration_eating(frameDuration), elapsedTime_eating(0.0f), currentFrame_eating(0), isAnimating_eating(false) {};
    Eating(){}
    virtual void startAnimation_eating()=0;
    virtual void update_eating(float deltaTime)=0;
    virtual void draw_eating(sf::RenderWindow& window)=0;
    sf::Sprite sprite_eating;
    sf::Texture texture_eating;
    float frameDuration_eating;
    int currentFrame_eating;
    float elapsedTime_eating;
    bool isAnimating_eating;
    sf::Vector2f position_eating;
    sf::Vector2f originalPosition_eating;
    virtual void updateSpriteRect_eating()=0;
    virtual ~Eating() {}
};

#endif // EATING_H
