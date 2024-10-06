#include "Sleeping.h"

// Constructor to load the sprite sheet for Sleeping Sleeping with scaling
Sleeping::Sleeping(const std::string& spriteSheetPath, float frameDuration, float scaleX, float scaleY)
    : frameDuration(frameDuration), currentFrame(0), isAnimating(false)
{
    // Load the sprite sheet
    if (!texture.loadFromFile(spriteSheetPath))
    {
        std::cerr << "Error loading sprite sheet: " << spriteSheetPath << std::endl;
    }

    // Set up the initial sprite
    sprite.setTexture(texture);

    // Center the sprite in the window
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

    // Set the scale for the sprite
    sprite.setScale(scaleX, scaleY); // Apply scaling

    // Initialize the first frame
    updateSpriteRect();
}

// Start the Sleeping
void Sleeping::startAnimation()
{
    isAnimating = true;
    currentFrame = 0; // Reset to first frame
    elapsedTime = 0.0f; // Reset elapsed time

    // Center the sprite's position in the window
    position.x = 400.f; // Center X position
    position.y = 300.f; // Center Y position
    sprite.setPosition(position); // Set the sprite's initial position
}

// Update the Sleeping based on the time elapsed
void Sleeping::update(float deltaTime)
{
    if (!isAnimating) return; // Do not update if not animating

    // Accumulate time
    elapsedTime += deltaTime;

    // Show each frame for a specified duration
    if (elapsedTime >= frameDuration)
    {
        currentFrame = (currentFrame + 1) % 6; // Cycle through all 6 frames
        elapsedTime = 0.0f; // Reset elapsed time
    }

    // Update the sprite's texture rectangle based on the current frame
    updateSpriteRect();
}

// Draw the Sleeping sprite
void Sleeping::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

// Update the sprite rectangle based on the current frame
void Sleeping::updateSpriteRect()
{
    // Calculate the frame size based on the sprite sheet
    int frameWidth = texture.getSize().x / 3;  // There are 3 columns
    int frameHeight = texture.getSize().y; // There is 1 row

    // x and y coordinates of the top-left corner of the frame in the sprite sheet
    int frameX = 0;
    int frameY = 0;

    // Determine which frame to use based on currentFrame
    switch (currentFrame)
    {
        case 0: // First frame (Row 1, Column 1)
            frameX = 0;
            frameY = 0;
            break;
        case 1: // Second frame (Row 1, Column 2)
            frameX = frameWidth; // Move right by one frame width
            frameY = 0;          // Still in the top row
            break;
        case 2: // Third frame (Row 1, Column 3)
            frameX = frameWidth * 2; // Move to the third frame
            frameY = 0; // Still in the top row
            break;
    }

    // Set the texture rectangle for the sprite
    sprite.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    // Optional: Print out the frame's coordinates for debugging
    std::cout << "Frame " << currentFrame << ": (X: " << frameX << ", Y: " << frameY << ")" << std::endl;
}
