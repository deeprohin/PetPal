#include <SFML/Graphics.hpp>
#include <iostream>

class Shower {
public:
    // Constructor to load the sprite sheet for an activity with scaling
    Shower(const std::string& spriteSheetPath, float frameDuration, float scaleX = 1.0f, float scaleY = 1.0f)
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
    void startAnimation() {
        isAnimating = true;
        currentFrame = 0; // Reset to the first frame
        elapsedTime = 0.0f; // Reset elapsed time
        position.x = 400.f; // Start position (center of the window)
        position.y = 300.f; // Y position
        originalPosition = position; // Store the original position
        sprite.setPosition(position); // Set the sprite's initial position
    }

    // Update the animation based on the time elapsed
    void update(float deltaTime) {
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
    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

private:
    sf::Sprite sprite;       // Sprite to display the current frame of the activity
    sf::Texture texture;     // Texture for the sprite sheet
    float frameDuration;     // Duration for showing each frame
    int currentFrame;        // Current frame index
    float elapsedTime = 0.0f; // Time elapsed since the last frame switch
    bool isAnimating;        // Flag to control whether animation is active
    sf::Vector2f position;   // Current position of the sprite
    sf::Vector2f originalPosition; // Store the original position of the sprite

    // Update the sprite rectangle based on the current frame
    void updateSpriteRect() {
        // Calculate the frame size based on the sprite sheet
        int frameWidth = texture.getSize().x / 5;  // There are 5 columns in the first row
        int frameHeight = texture.getSize().y; // Only 1 row in the sprite sheet

        // x and y coordinates of the top-left corner of the frame in the sprite sheet
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
            case 2: // Third frame (Row 1, Column 3)
                frameX = 2 * frameWidth; // Move right by two frame widths
                frameY = 0; 
                break;
            case 3: // Fourth frame (Row 1, Column 4)
                frameX = 3 * frameWidth; // Move right by three frame widths
                frameY = 0; 
                break;
            case 4: // Fifth frame (Row 1, Column 5)
                frameX = 4 * frameWidth; // Move right by four frame widths
                frameY = 0; 
                break;
        }

        // Set the texture rectangle for the sprite
        sprite.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));
        
        // Optional: Print out the frame's coordinates for debugging
        std::cout << "Frame " << currentFrame << ": (X: " << frameX << ", Y: " << frameY << ")" << std::endl;
    }
};

int main() {
    // Create a window (800x600)
    sf::RenderWindow window(sf::VideoMode(800, 600), "Shower Animation");

    // Frame limit for smooth display
    window.setFramerateLimit(60);

    // Load the sprite sheet for the "shower" activity with scaling
    Shower shower("Big2/showering/spritesheet.png", 1.4f, 2.9f, 2.9f);  // Adjust frame duration and scaling

    // Start the animation
    shower.startAnimation();

    // Main game loop
    sf::Clock clock; // Clock to track time
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Get the time elapsed since the last frame
        float deltaTime = clock.restart().asSeconds();

        // Update the shower animation
        shower.update(deltaTime);

        // Clear the window
        window.clear(sf::Color(245, 245, 220));

        // Draw the shower
        shower.draw(window);

        // Display the window contents
        window.display();
    }

    return 0;
}
