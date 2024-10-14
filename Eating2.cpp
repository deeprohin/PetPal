// Eating.cpp
#include "Eating.h"

Eating::Eating(const std::string& spriteSheetPath, float frameDuration, float scaleX, float scaleY)
    : frameDuration(frameDuration), currentFrame(0), isAnimating(false) 
{
    // Load the sprite sheet texture
    if (!texture.loadFromFile(spriteSheetPath)) {
        std::cerr << "Error loading sprite sheet: " << spriteSheetPath << std::endl;
    }

    // Set up the initial sprite
    sprite.setTexture(texture);
    
    // Apply scaling to the sprite
    sprite.setScale(scaleX, scaleY);

    // Initialize the first frame (top left)
    updateSpriteRect();
}

void Eating::startAnimation() {
    isAnimating = true;
    currentFrame = 0; // Reset to first frame
    elapsedTime = 0.0f; // Reset elapsed time
    position.x = 400.f; // Start position (center of the window)
    position.y = 300.f; // Y position
    originalPosition = position; // Store the original position
    sprite.setPosition(position); // Set the sprite's initial position
}

void Eating::update(float deltaTime) {
    if (!isAnimating) return; // Do not update if not animating

    // Accumulate time
    elapsedTime += deltaTime;

    // Show the first frame for a specified duration, then alternate frames
    switch (currentFrame) {
        case 0:
            // Stay on the first frame for the duration
            if (elapsedTime >= frameDuration) {
                currentFrame = 1; // Move to the second frame
                position.x -= 3;  // Move left 3 units
                sprite.setPosition(position); // Update the sprite's position
                elapsedTime = 0.0f; // Reset elapsed time
            }
            break;
        case 1:
            // Stay on the second frame for a short duration
            if (elapsedTime >= frameDuration / 2) {
                currentFrame = 2; // Move to the third frame
                elapsedTime = 0.0f; // Reset elapsed time
            }
            break;
        case 2:
            // Return to original position after showing the third frame
            if (elapsedTime >= frameDuration / 2) {
                position = originalPosition; // Return to original position
                sprite.setPosition(position); // Update the sprite's position
                currentFrame = 0; // Reset back to first frame
                elapsedTime = 0.0f; // Reset elapsed time
            }
            break;
    }

    // Update the sprite's texture rectangle based on the current frame
    updateSpriteRect();
}

void Eating::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Eating::updateSpriteRect() {
    // Calculate the frame size based on the sprite sheet
    int frameWidth = texture.getSize().x / 2;  // Two columns (frames) in the first row
    int frameHeight = texture.getSize().y / 2; // Two rows, but the second row has only one frame

    // Determine which frame to use based on currentFrame
    int frameX = (currentFrame == 1) ? frameWidth : 0; // Second frame is to the right
    int frameY = (currentFrame == 2) ? frameHeight : 0; // Third frame is below the first frame

    // Set the texture rectangle for the sprite
    sprite.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    // Optional: Print out the frame's coordinates for debugging
    std::cout << "Frame " << currentFrame << ": (X: " << frameX << ", Y: " << frameY << ")" << std::endl;
}
