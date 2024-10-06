#include "Sleeping.h"
#include <iostream>

Sleeping::Sleeping(const std::string& spriteSheetPath, float frameDuration, float scaleX, float scaleY)
    : frameDuration(frameDuration), currentFrame(0), isAnimating(false), elapsedTime(0.0f) {
    if (!texture.loadFromFile(spriteSheetPath)) {
        std::cerr << "Error loading sprite sheet: " << spriteSheetPath << std::endl;
        return;
    }

    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setScale(scaleX, scaleY);
    updateSpriteRect();
}

void Sleeping::startAnimation() {
    isAnimating = true;
    currentFrame = 0;
    elapsedTime = 0.0f;
    position.x = 400.f;
    position.y = 300.f;
    sprite.setPosition(position);
}

void Sleeping::update(float deltaTime) {
    if (!isAnimating) return;

    elapsedTime += deltaTime;

    if (elapsedTime >= frameDuration) {
        currentFrame = (currentFrame + 1) % 6;
        elapsedTime = 0.0f;
    }

    updateSpriteRect();
}

void Sleeping::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Sleeping::updateSpriteRect() {
    int frameWidth = texture.getSize().x / 2;
    int frameHeight = texture.getSize().y / 2;
    int frameX = 0;
    int frameY = 0;

    switch (currentFrame) {
        case 0:
            frameX = 0;
            frameY = 0;
            break;
        case 1:
            frameX = frameWidth;
            frameY = 0;
            break;
        case 2:
            frameX = 0;
            frameY = frameHeight;
            break;
        case 3:
            frameX = frameWidth;
            frameY = frameHeight;
            break;
        case 4:
            frameX = 0;
            frameY = frameHeight * 2;
            break;
        case 5:
            frameX = frameWidth;
            frameY = frameHeight * 2;
            break;
    }

    sprite.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    // Optional debug output
    std::cout << "Frame " << currentFrame << ": (X: " << frameX << ", Y: " << frameY << ")" << std::endl;
}
