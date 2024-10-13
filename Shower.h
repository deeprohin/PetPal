#ifndef SHOWER_H
#define SHOWER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Shower {
public:
    //showering implimentation:                  
    Shower(const std::string& spriteSheetPath, float frameDuration, float scaleX = 1.0f, float scaleY = 1.0f): frameDuration_shower(frameDuration), elapsedTime_shower(0.0f), currentFrame_shower(0), isAnimating_shower(false) {}
    virtual void startAnimation_shower()=0;
    virtual void update_shower(float deltaTime)=0;
    virtual void draw_shower(sf::RenderWindow& window)=0;
    sf::Sprite sprite_shower;
    sf::Texture texture_shower;
    float frameDuration_shower;
    int currentFrame_shower;
    float elapsedTime_shower;
    bool isAnimating_shower;
    sf::Vector2f position_shower;
    sf::Vector2f originalPosition_shower;
    virtual void updateSpriteRect_shower()=0;
    virtual ~Shower() {}
};
#endif // SHOWER_H