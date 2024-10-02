#include "Medicine.h"

// Constructor to load the sprite sheet for an activity with scaling
Medicine::Medicine(const std::string& spriteSheetPath, float frameDuration, float scaleX, float scaleY)
    : frameDuration(frameDuration), currentFrame(0), isAnimating(false) {
    // Load the sprite sheet
    if (!texture.loadFromFile(spriteSheetPath)) {
        std::cerr << "Error loading sprite sheet: " << spriteSheetPath << std::endl;
        return; // Exit if texture fails to load
    }

    // Set up the initial sprite
    sprite.setTexture(texture);
    
    // Set the sprite's position to center of the window
    sprite.setPosition(400 - (texture.getSize().x / 2), 300 - (texture.getSize().y / 2));

    // Apply scaling to the sprite
    sprite.setScale(scaleX, scaleY);

    // Initialize the first frame
    updateSpriteRect();
}

// Start the Medicine animation
void Medicine::startAnimation() {
    isAnimating = true;
    currentFrame = 0; // Reset to first frame
    elapsedTime = 0.0f; // Reset elapsed time
}

// Update the Medicine based on the time elapsed
void Medicine::update(float deltaTime) {
    if (!isAnimating) return; // Do not update if not animating

    // Accumulate time
    elapsedTime += deltaTime;

    // Show each frame for a specified duration
    if (elapsedTime >= frameDuration) {
        currentFrame = (currentFrame + 1) % 2; // Switch between 0 and 1 (two frames)
        elapsedTime = 0.0f; // Reset elapsed time
    }

    // Update the sprite's texture rectangle based on the current frame
    updateSpriteRect();
}

// Draw the Medicine sprite
void Medicine::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    // Debugging output to check sprite position
    std::cout << "Drawing sprite at: (" << sprite.getPosition().x << ", " << sprite.getPosition().y << ")" << std::endl;
}

// Update the sprite rectangle based on the current frame
void Medicine::updateSpriteRect() {
    // Frame dimensions based on the sprite sheet
    int frameWidth = 32;  // Width of one frame
    int frameHeight = 36; // Height of one frame

    int frameX = 0;
    int frameY = 0;

    // Determine which frame to use based on currentFrame
    switch (currentFrame) {
        case 0: // First frame (Row 1, Column 1)
            frameX = 0;
            frameY = 0;
            break;
        case 1: // Second frame (Row 1, Column 2)
            frameX = frameWidth; // Move right by one frame width
            frameY = 0;          // Still in the top row
            break;
    }

    // Set the texture rectangle for the sprite
    sprite.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    // Debugging output to check the frame rect
    std::cout << "Frame rect set: (X: " << frameX << ", Y: " << frameY << ", Width: " << frameWidth << ", Height: " << frameHeight << ")" << std::endl;
}
