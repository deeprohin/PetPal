#ifndef MEDICINE_H
#define MEDICINE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Medicine {
public:
    Medicine(const std::string& spriteSheetPath, float frameDuration, float scaleX = 1.0f, float scaleY = 1.0f);

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

    void updateSpriteRect();
};

#endif // MEDICINE_H
