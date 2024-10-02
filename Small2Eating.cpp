#include "Eating.h"

// Constructor to load the sprite sheet with scaling
Eating::Eating(const std::string& spriteSheetPath, float frameDuration, float scaleX, float scaleY)
    : frameDuration(frameDuration), currentFrame(0), isAnimating(false) {
    // Load the sprite sheet
    if (!texture.loadFromFile(spriteSheetPath)) {
        std::cerr << "Error loading sprite sheet: " << spriteSheetPath << std::endl;
    }

    // Set up the initial sprite
    sprite.setTexture(texture);
    sprite.setScale(scaleX, scaleY);

    // Initialize the first frame (top left)
    updateSpriteRect();
}

// Start the Eating
void Eating::startAnimation() {
    isAnimating = true;
    currentFrame = 0;
    elapsedTime = 0.0f;
    position.x = 400.f;
    position.y = 300.f;
    originalPosition = position;
    sprite.setPosition(position);
}

// Update the Eating based on time
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

// Draw the Eating sprite
void Eating::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

// Update the sprite rectangle based on the current frame
void Eating::updateSpriteRect() {
    int frameWidth = texture.getSize().x / 3;
    int frameHeight = texture.getSize().y;

    int frameX = 0;
    int frameY = 0;

    switch (currentFrame) {
        case 0: frameX = 0; break;
        case 1: frameX = frameWidth; break;
        case 2: frameX = 2 * frameWidth; break;
    }

    sprite.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));
    std::cout << "Frame " << currentFrame << ": (X: " << frameX << ", Y: " << frameY << ")" << std::endl;
}
