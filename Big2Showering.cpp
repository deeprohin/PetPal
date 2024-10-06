#include "Shower.h"

// Constructor to load the sprite sheet for an activity with scaling
Shower::Shower(const std::string& spriteSheetPath, float frameDuration, float scaleX, float scaleY)
    : frameDuration(frameDuration), currentFrame(0), isAnimating(false) {
    // Load the sprite sheet
    if (!texture.loadFromFile(spriteSheetPath)) {
        std::cerr << "Error loading sprite sheet: " << spriteSheetPath << std::endl;
    }

    // Set up the initial sprite
    sprite.setTexture(texture);

    // Apply scaling to the sprite
    sprite.setScale(scaleX, scaleY);

    // Update the texture rectangle for the initial frame
    updateSpriteRect();
}

// Start the animation
void Shower::startAnimation() {
    isAnimating = true;
    currentFrame = 0; // Reset to the first frame
    elapsedTime = 0.0f; // Reset elapsed time
    position.x = 400.f; // Start position (center of the window)
    position.y = 300.f; // Y position
    originalPosition = position; // Store the original position
    sprite.setPosition(position); // Set the sprite's initial position
}

// Update the animation based on the time elapsed
void Shower::update(float deltaTime) {
    if (!isAnimating) return; // Do not update if not animating

    // Accumulate time
    elapsedTime += deltaTime;

    // Switch frames based on elapsed time
    if (elapsedTime >= frameDuration) {
        currentFrame = (currentFrame + 1) % 5; // Loop back to the first frame after the last one
        elapsedTime = 0.0f; // Reset elapsed time
    }

    // Update the sprite's texture rectangle based on the current frame
    updateSpriteRect();
}

// Draw the shower sprite
void Shower::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

// Update the sprite rectangle based on the current frame
void Shower::updateSpriteRect() {
    // Calculate the frame size based on the sprite sheet
    int frameWidth = texture.getSize().x / 5;  // There are 5 columns in the first row
    int frameHeight = texture.getSize().y; // Only 1 row in the sprite sheet

    // x and y coordinates of the top-left corner of the frame in the sprite sheet
    int frameX = 0;
    int frameY = 0;

    // Determine which frame to use based on currentFrame
    switch (currentFrame) {
        case 0: frameX = 0; break;
        case 1: frameX = frameWidth; break;
        case 2: frameX = 2 * frameWidth; break;
        case 3: frameX = 3 * frameWidth; break;
        case 4: frameX = 4 * frameWidth; break;
    }

    // Set the texture rectangle for the sprite
    sprite.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));
    
    // Optional: Print out the frame's coordinates for debugging
    std::cout << "Frame " << currentFrame << ": (X: " << frameX << ", Y: " << frameY << ")" << std::endl;
}
