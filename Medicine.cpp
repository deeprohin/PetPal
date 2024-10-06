#include "Medicine.h"

Medicine::Medicine(const std::string& spriteSheetPath, float frameDuration, float scaleX, float scaleY)
    : frameDuration(frameDuration), currentFrame(0), isAnimating(false), elapsedTime(0.0f) 
{
    if (!texture.loadFromFile(spriteSheetPath)) {
        std::cerr << "Error loading sprite sheet: " << spriteSheetPath << std::endl;
        return;
    }

    sprite.setTexture(texture);
    sprite.setPosition(400 - (texture.getSize().x / 2), 300 - (texture.getSize().y / 2));
    sprite.setScale(scaleX, scaleY);

    updateSpriteRect();
}

void Medicine::startAnimation() {
    isAnimating = true;
    currentFrame = 0;
    elapsedTime = 0.0f;
}

void Medicine::update(float deltaTime) {
    if (!isAnimating) return;

    elapsedTime += deltaTime;

    if (elapsedTime >= frameDuration) {
        currentFrame = (currentFrame + 1) % 2;  // Switch between 2 frames
        elapsedTime = 0.0f;
    }

    updateSpriteRect();
}

void Medicine::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    std::cout << "Drawing sprite at: (" << sprite.getPosition().x << ", " << sprite.getPosition().y << ")" << std::endl;
}

void Medicine::updateSpriteRect() {
    int frameWidth = 32;
    int frameHeight = 32;

    int frameX = 0;
    int frameY = currentFrame * frameHeight;  // Determine Y position based on current frame

    sprite.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    std::cout << "Frame rect set: (X: " << frameX << ", Y: " << frameY << ", Width: " << frameWidth << ", Height: " << frameHeight << ")" << std::endl;
}
