#ifndef SHOWER_H
#define SHOWER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Shower {
public:
    Shower(const std::string& spriteSheetPath, float frameDuration, float scaleX = 1.0f, float scaleY = 1.0f){}
    virtual void startAnimation(){}
    virtual void update(float deltaTime){}
    virtual void draw(sf::RenderWindow& window){}
    sf::Sprite sprite;
    sf::Texture texture;
    float frameDuration;
    int currentFrame;
    float elapsedTime;
    bool isAnimating;
    sf::Vector2f position;
    sf::Vector2f originalPosition;
    virtual void updateSpriteRect(){}
};

#endif // SHOWER_H