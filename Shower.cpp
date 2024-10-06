#include "Shower.h"

Shower::Shower(const std::string& spriteSheetPath, float frameDuration, float scaleX, float scaleY)
    : frameDuration(frameDuration), currentFrame(0), isAnimating(false), elapsedTime(0.0f)
{
    if (!texture.loadFromFile(spriteSheetPath)) {
        std::cerr << "Error loading sprite sheet: " << spriteSheetPath << std::endl;
    }

    sprite.setTexture(texture);
    sprite.setScale(scaleX, scaleY);
    updateSpriteRect();
}

void Shower::startAnimation() {
    isAnimating = true;
    currentFrame = 0;
    elapsedTime = 0.0f;
    position.x = 400.f;
    position.y = 300.f;
    originalPosition = position;
    sprite.setPosition(position);
}

void Shower::update(float deltaTime) {
    if (!isAnimating) return;

    elapsedTime += deltaTime;

    if (elapsedTime >= frameDuration) {
        currentFrame = (currentFrame + 1) % 4; // Assuming 4 frames for this example
        elapsedTime = 0.0f;
    }

    updateSpriteRect();
}

void Shower::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Shower::updateSpriteRect() {
    int frameWidth = texture.getSize().x / 2;
    int frameHeight = texture.getSize().y / 2;

    int frameX = (currentFrame % 2) * frameWidth;
    int frameY = (currentFrame / 2) * frameHeight;

    sprite.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    std::cout << "Frame " << currentFrame << ": (X: " << frameX << ", Y: " << frameY << ")" << std::endl;
}
