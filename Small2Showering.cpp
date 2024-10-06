#include "Shower.h"

// Constructor to load the sprite sheet with scaling
Shower::Shower(const std::string& spriteSheetPath, float frameDuration, float scaleX, float scaleY)
    : frameDuration(frameDuration), currentFrame(0), isAnimating(false) {
    
    // Load the sprite sheet
    if (!texture.loadFromFile(spriteSheetPath)) {
        std::cerr << "Error loading sprite sheet: " << spriteSheetPath << std::endl;
        return;  // Early return if texture fails to load
    }

    // Set up the initial sprite
    sprite.setTexture(texture);
    position.x = 400.f; // Center of the window
    position.y = 300.f;
    sprite.setPosition(position); // Set initial position
    sprite.setScale(scaleX, scaleY); // Apply scaling
    updateSpriteRect(); // Initialize first frame

    // Debug output to check sprite setup
    std::cout << "Sprite loaded and positioned at: (" << position.x << ", " << position.y << ")" << std::endl;
}

// Start the Shower
void Shower::startAnimation() {
    isAnimating = true;
    currentFrame = 0;  // Reset to first frame
    elapsedTime = 0.0f;  // Reset elapsed time
}

// Update the Shower based on time elapsed
void Shower::update(float deltaTime) {
    if (!isAnimating) return;  // Do not update if not animating

    elapsedTime += deltaTime;  // Accumulate time

    // Switch frames based on elapsed time
    if (elapsedTime >= frameDuration) {
        currentFrame = (currentFrame + 1) % 5;  // Loop through 5 frames
        elapsedTime = 0.0f;  // Reset elapsed time
    }

    updateSpriteRect();  // Update the sprite's texture rectangle
}

// Draw the Shower sprite
void Shower::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

// Update the sprite rectangle based on the current frame
void Shower::updateSpriteRect() {
    int frameWidth = texture.getSize().x / 5;  // Assuming 5 frames horizontally
    int frameHeight = texture.getSize().y;  // Height remains the same

    // Set the frame x coordinate based on the current frame
    int frameX = currentFrame * frameWidth;

    // Set the texture rectangle for the sprite
    sprite.setTextureRect(sf::IntRect(frameX, 0, frameWidth, frameHeight));

    // Debug output to check the frame being drawn
    std::cout << "Current Frame: " << currentFrame << " (X: " << frameX << ", Width: " << frameWidth << ")" << std::endl;
}
