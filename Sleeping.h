#ifndef SLEEPING_H
#define SLEEPING_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Sleeping
{
public:
    Sleeping(const std::string& spriteSheetPath, float frameDuration, float scaleX = 1.0f, float scaleY = 1.0f);

    void startAnimation();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    sf::Sprite sprite;
    sf::Texture texture;
    float frameDuration;
    int currentFrame;
    float elapsedTime;
    bool isAnimating;
    sf::Vector2f position;

    void updateSpriteRect();
};

#endif // SLEEPING_H
