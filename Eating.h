#ifndef EATING_H
#define EATING_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Eating {
public:
    Eating(const std::string& spriteSheetPath, float frameDuration, float scaleX, float scaleY){};
    virtual void startAnimation_eating();
    virtual void update_eating(float deltaTime);
    virtual void draw_eating(sf::RenderWindow& window);
    sf::Sprite sprite_eating;
    sf::Texture texture_eating;
    float frameDuration_eating;
    int currentFrame_eating;
    float elapsedTime_eating;
    bool isAnimating_eating;
    sf::Vector2f position_eating;
    sf::Vector2f originalPosition_eating;
    virtual void updateSpriteRect_eating();
};

#endif // EATING_H
