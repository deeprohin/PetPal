// Medicine.cpp
#include "Medicine.h"
#include <iostream>

Medicine::Medicine(const std::string& spriteSheetPath, float frameDuration, float scaleX, float scaleY)
    : frameDuration(frameDuration), currentFrame(0), isAnimating(false), elapsedTime(0.0f) 
{
    // Load the sprite sheet texture
    if (!texture.loadFromFile(spriteSheetPath)) {
        std::cerr << "Error loading sprite sheet: " << spriteSheetPath << std::endl;
        return; // Exit if texture fails to load
    }

    // Set up the sprite with the texture and scale it
    sprite.setTexture(texture);
    sprite.setScale(scaleX, scaleY);

    // Set sprite to the center of the screen (adjust based on texture size)
    sprite.setPosition(400 - (texture.getSize().x / 2), 300 - (texture.getSize().y / 2));

    // Initialize the first frame of the animation
    updateSpriteRect();
}

void Medicine::startAnimation() {
    isAnimating = true;
    currentFrame = 0;
    elapsedTime = 0.0f;
}

void Medicine::update(float deltaTime) {
    if (!isAnimating) return;  // If not animating, do nothing

    // Update the time elapsed
    elapsedTime += deltaTime;

    // If enough time has passed, move to the next frame
    if (elapsedTime >= frameDuration) {
        currentFrame = (currentFrame + 1) % 2;  // 2 frames, loop between them
        elapsedTime = 0.0f;  // Reset time for the next frame
    }

    // Update the texture rectangle for the current frame
    updateSpriteRect();
}

void Medicine::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    // Debugging output to check sprite position
    std::cout << "Drawing sprite at: (" << sprite.getPosition().x << ", " << sprite.getPosition().y << ")" << std::endl;
}

void Medicine::updateSpriteRect() {
    // Each frame is 32x32 pixels
    int frameWidth = 32;
    int frameHeight = 32;

    // Determine the top-left corner of the frame in the sprite sheet
    int frameX = 0;
    int frameY = currentFrame * frameHeight; // Switch between 0 and 32 in Y direction

    // Set the texture rectangle for the sprite
    sprite.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    // Debugging output to check frame rectangle
    std::cout << "Frame rect set: (X: " << frameX << ", Y: " << frameY << ", Width: " << frameWidth << ", Height: " << frameHeight << ")" << std::endl;
}
