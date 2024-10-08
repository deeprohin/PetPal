#ifndef SLEEPING_H
#define SLEEPING_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Sleeping{
public:
    Sleeping(const std::string& spriteSheetPath, float frameDuration, float scaleX = 1.0f, float scaleY = 1.0f): frameDuration_sleeping(frameDuration), elapsedTime_sleeping(0.0f), currentFrame_sleeping(0), isAnimating_sleeping(false){};
    virtual void startAnimation_sleeping(){}
    virtual void update_sleeping(float deltaTime){}
    virtual void draw_sleeping(sf::RenderWindow& window){}
    sf::Sprite sprite_sleeping;
    sf::Texture texture_sleeping;
    float frameDuration_sleeping;
    int currentFrame_sleeping;
    float elapsedTime_sleeping;
    bool isAnimating_sleeping;
    sf::Vector2f position_sleeping;
    virtual void updateSpriteRect_sleeping(){}
};

#endif // SLEEPING_H
