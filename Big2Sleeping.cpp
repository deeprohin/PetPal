#include "Sleeping.h"

// Constructor to load the sprite sheet for sleeping animation with scaling
Sleeping::Sleeping(const std::string& spriteSheetPath, float frameDuration, float scaleX, float scaleY)
    : frameDuration(frameDuration), currentFrame(0), isAnimating(false) {
    // Load the sprite sheet
    if (!texture.loadFromFile(spriteSheetPath)) {
        std::cerr << "Error loading sprite sheet: " << spriteSheetPath << std::endl;
    }

    // Set up the initial sprite
    sprite.setTexture(texture);
    
    // Apply scaling to the sprite
    sprite.setScale(scaleX, scaleY);

    // Center the sprite in the window
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    
    // Initialize the first frame
    updateSpriteRect();
}

// Start the animation
void Sleeping::startAnimation() {
    isAnimating = true;
    currentFrame = 0; // Reset to first frame
    elapsedTime = 0.0f; // Reset elapsed time

    // Center the sprite's position in the window
    position.x = 400.f; // Center X position
    position.y = 300.f; // Center Y position
    sprite.setPosition(position); // Set the sprite's initial position
}

// Update the animation based on the time elapsed
void Sleeping::update(float deltaTime) {
    if (!isAnimating) return; // Do not update if not animating

    // Accumulate time
    elapsedTime += deltaTime;

    // Show each frame for a specified duration
    if (elapsedTime >= frameDuration) {
        currentFrame = (currentFrame + 1) % 6; // Cycle through all 6 frames
        elapsedTime = 0.0f; // Reset elapsed time
    }

    // Update the sprite's texture rectangle based on the current frame
    updateSpriteRect();
}

// Draw the sleeping sprite
void Sleeping::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

// Update the sprite rectangle based on the current frame
void Sleeping::updateSpriteRect() {
    // Calculate the frame size based on the sprite sheet
    int frameWidth = texture.getSize().x / 4;  // There are 4 columns
    int frameHeight = texture.getSize().y; // There is 1 row

    // x and y coordinates of the top-left corner of the frame in the sprite sheet
    int frameX = 0;
    int frameY = 0;

    // Determine which frame to use based on currentFrame
    switch (currentFrame) {
        case 0: frameX = 0; break;                          // First frame
        case 1: frameX = frameWidth; break;                // Second frame
        case 2: frameX = 2 * frameWidth; break;            // Third frame
        case 3: frameX = 3 * frameWidth; break;            // Fourth frame
        case 4: frameX = 4 * frameWidth; break;            // Fifth frame
        case 5: frameX = 5 * frameWidth; break;            // Sixth frame (if needed)
    }

    // Set the texture rectangle for the sprite
    sprite.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    // Optional: Print out the frame's coordinates for debugging
    std::cout << "Frame " << currentFrame << ": (X: " << frameX << ", Y: " << frameY << ")" << std::endl;
}
