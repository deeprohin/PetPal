#include <SFML/Graphics.hpp>
#include <iostream>

class Sleeping {
public:
    // Constructor to load the sprite sheet for sleeping animation with scaling
    Sleeping(const std::string& spriteSheetPath, float frameDuration, float scaleX = 1.0f, float scaleY = 1.0f)
        : frameDuration(frameDuration), currentFrame(0), isAnimating(false) {
        // Load the sprite sheet
        if (!texture.loadFromFile(spriteSheetPath)) {
            std::cerr << "Error loading sprite sheet: " << spriteSheetPath << std::endl;
        }

        // Set up the initial sprite
        sprite.setTexture(texture);

        // Center the sprite in the window
        sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

        // Apply scaling to the sprite
        sprite.setScale(scaleX, scaleY);
        
        // Initialize the first frame
        updateSpriteRect();
    }

    // Start the animation
    void startAnimation() {
        isAnimating = true;
        currentFrame = 0; // Reset to first frame
        elapsedTime = 0.0f; // Reset elapsed time

        // Center the sprite's position in the window
        position.x = 400.f; // Center X position
        position.y = 300.f; // Center Y position
        sprite.setPosition(position); // Set the sprite's initial position
    }

    // Update the animation based on the time elapsed
    void update(float deltaTime) {
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
    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

private:
    sf::Sprite sprite;       // Sprite to display the current frame of the activity
    sf::Texture texture;     // Texture for the sprite sheet
    float frameDuration;     // Duration for showing each frame
    int currentFrame;        // Current frame index (0 to 5)
    float elapsedTime = 0.0f; // Time elapsed since the last frame switch
    bool isAnimating;        // Flag to control whether animation is active
    sf::Vector2f position;   // Current position of the sprite

    // Update the sprite rectangle based on the current frame
    void updateSpriteRect() {
        // Calculate the frame size based on the sprite sheet
        int frameWidth = texture.getSize().x / 2;  // There are 2 columns
        int frameHeight = texture.getSize().y / 2; // There are 2 rows

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
            case 2: // Third frame (Row 2, Column 1)
                frameX = 0;           // Stay in the first column
                frameY = frameHeight; // Move down by one frame height (Row 2)
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
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sleeping Animation");

    // Frame limit for smooth display
    window.setFramerateLimit(60);

    // Load the sprite sheet for the "sleeping" activity with scaling
    Sleeping sleeping("Big/Sleeping.png", 1.4f, 2.9f, 2.9f);  // Adjust frame duration and scale

    // Start the animation
    sleeping.startAnimation();

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

        // Update the sleeping animation
        sleeping.update(deltaTime);

        // Clear the window
        window.clear(sf::Color(245, 245, 220)); // Optionally change the color for better visibility

        // Draw the sleeping sprite
        sleeping.draw(window);

        // Display the window contents
        window.display();
    }

    return 0;
}
