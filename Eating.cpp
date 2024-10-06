#include "Eating.h"

Eating::Eating(const std::string& spriteSheetPath, float frameDuration, float scaleX, float scaleY)
    : frameDuration(frameDuration), currentFrame(0), isAnimating(false), elapsedTime(0.0f) 
{
    if (!texture.loadFromFile(spriteSheetPath)) {
        std::cerr << "Error loading sprite sheet: " << spriteSheetPath << std::endl;
        return;
    }

    sprite.setTexture(texture);
    sprite.setScale(scaleX, scaleY);

    updateSpriteRect();
}

void Eating::startAnimation() {
    isAnimating = true;
    currentFrame = 0;
    elapsedTime = 0.0f;
    position.x = 400.f;
    position.y = 300.f;
    originalPosition = position;
    sprite.setPosition(position);
}

void Eating::update(float deltaTime) {
    if (!isAnimating) return;

    elapsedTime += deltaTime;

    if (currentFrame == 0) {
        if (elapsedTime >= frameDuration) {
            currentFrame = 1;
            position.x -= 3;
            sprite.setPosition(position);
            elapsedTime = 0.0f;
        }
    } else if (currentFrame == 1) {
        if (elapsedTime >= frameDuration / 2) {
            currentFrame = 2;
            elapsedTime = 0.0f;
        }
    } else if (currentFrame == 2) {
        if (elapsedTime >= frameDuration / 2) {
            position = originalPosition;
            sprite.setPosition(position);
            currentFrame = 0;
            elapsedTime = 0.0f;
        }
    }

    updateSpriteRect();
}

void Eating::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Eating::updateSpriteRect() {
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
    }

    sprite.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));
}
