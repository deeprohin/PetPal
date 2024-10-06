#include "Medicine.h"  // Including the Medicine header

// Constructor to load the sprite sheet for an activity with scaling
Medicine::Medicine(const std::string& spriteSheetPath, float frameDuration, float scaleX, float scaleY)
    : frameDuration(frameDuration), currentFrame(0), isAnimating(false) {
    
    // Load the sprite sheet
    if (!texture.loadFromFile(spriteSheetPath)) {
        std::cerr << "Error loading sprite sheet: " << spriteSheetPath << std::endl;
        return;  // Exit if the texture fails to load
    }

    // Set up the sprite with the texture
    sprite.setTexture(texture);
    
    // Set the sprite's position to center the window (adjust as needed)
    sprite.setPosition(400 - (texture.getSize().x / 2), 300 - (texture.getSize().y / 2));

    // Apply scaling to the sprite
    sprite.setScale(scaleX, scaleY);

    // Initialize the first frame
    updateSpriteRect();
}

// Start the Medicine
void Medicine::startAnimation() {
    isAnimating = true;
    currentFrame = 0;  // Start from the first frame
    elapsedTime = 0.0f;  // Reset elapsed time
}

// Update the Medicine based on the time elapsed
void Medicine::update(float deltaTime) {
    if (!isAnimating) return;

    // Accumulate elapsed time
    elapsedTime += deltaTime;

    // Switch frames based on the frame duration
    if (elapsedTime >= frameDuration) {
        currentFrame = (currentFrame + 1) % 2;  // Cycle between two frames
        elapsedTime = 0.0f;  // Reset elapsed time
    }

    // Update the sprite's texture rectangle based on the current frame
    updateSpriteRect();
}

// Draw the Medicine sprite
void Medicine::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    std::cout << "Drawing sprite at: (" << sprite.getPosition().x << ", " << sprite.getPosition().y << ")" << std::endl;
}

// Update the sprite's texture rectangle based on the current frame
void Medicine::updateSpriteRect() {
    int frameWidth = 32;  // Width of each frame
    int frameHeight = 32;  // Height of each frame

    // Determine which frame to use based on the current frame index
    int frameX = (currentFrame == 0) ? 0 : frameWidth;
    int frameY = 0;  // Single row, so Y coordinate is 0

    // Set the texture rectangle for the sprite
    sprite.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    // Debug output for frame information
    std::cout << "Frame rect set: (X: " << frameX << ", Y: " << frameY << ", Width: " << frameWidth << ", Height: " << frameHeight << ")" << std::endl;
}
