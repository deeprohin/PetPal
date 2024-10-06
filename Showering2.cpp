// Shower.cpp
#include "Shower.h"
#include <iostream>

Shower::Shower(const std::string& spriteSheetPath, float frameDuration, float scaleX, float scaleY)
    : frameDuration(frameDuration), currentFrame(0), isAnimating(false), elapsedTime(0.0f) 
{
    // Load the sprite sheet texture
    if (!texture.loadFromFile(spriteSheetPath)) {
        std::cerr << "Error loading sprite sheet: " << spriteSheetPath << std::endl;
    }

    // Set up the sprite with the texture and scale it
    sprite.setTexture(texture);
    sprite.setScale(scaleX, scaleY);

    // Initialize the first frame of the animation
    updateSpriteRect();
}

void Shower::startAnimation() {
    isAnimating = true;
    currentFrame = 0;
    elapsedTime = 0.0f;
    position.x = 400.f;
    position.y = 300.f;
    originalPosition = position;
    sprite.setPosition(position);  // Set sprite to the center
}

void Shower::update(float deltaTime) {
    if (!isAnimating) return;  // If not animating, do nothing

    // Update the time elapsed
    elapsedTime += deltaTime;

    // If enough time has passed, move to the next frame
    if (elapsedTime >= frameDuration) {
        currentFrame = (currentFrame + 1) % 4;  // 4 frames, loop back to the first
        elapsedTime = 0.0f;  // Reset time for next frame
    }

    // Update the texture rectangle for the current frame
    updateSpriteRect();
}

void Shower::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Shower::updateSpriteRect() {
    // Each frame is half of the sprite sheet's width and height
    int frameWidth = texture.getSize().x / 2;  // 2 columns
    int frameHeight = texture.getSize().y / 2; // 2 rows

    // Calculate the top-left corner of the frame based on the current frame index
    int frameX = (currentFrame % 2) * frameWidth;  // 0 or 1 for columns
    int frameY = (currentFrame / 2) * frameHeight; // 0 or 1 for rows

    // Set the sprite's texture rectangle to display the correct frame
    sprite.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    // Optional debug print to check which frame is currently being displayed
    std::cout << "Frame " << currentFrame << ": (X: " << frameX << ", Y: " << frameY << ")" << std::endl;
}
