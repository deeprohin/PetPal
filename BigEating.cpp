#include <SFML/Graphics.hpp>
#include <iostream>

class Eating {
public:
    // Constructor to load the sprite sheet for an activity with scaling
    Eating(const std::string& spriteSheetPath, float frameDuration, float scaleX = 1.0f, float scaleY = 1.0f)
        : frameDuration(frameDuration), currentFrame(0), isAnimating(false) {
        // Load the sprite sheet
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

    // Start the animation
    void startAnimation() {
        isAnimating = true;
        currentFrame = 0; // Reset to first frame
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

        // Show the first frame for a specified duration, then alternate frames
        if (currentFrame == 0) {
            // Stay on the first frame for the duration
            if (elapsedTime >= frameDuration) {
                currentFrame = 1; // Move to the second frame (top right)
                position.x -= 3;  // Move left 3 units
                sprite.setPosition(position); // Update the sprite's position
                elapsedTime = 0.0f; // Reset elapsed time
            }
        } else if (currentFrame == 1) {
            // Stay on the second frame for a short duration before returning
            if (elapsedTime >= frameDuration / 2) {
                currentFrame = 2; // Move to the third frame (bottom left)
                elapsedTime = 0.0f; // Reset elapsed time
            }
        } else if (currentFrame == 2) {
            // Return to original position after showing the bottom left frame
            if (elapsedTime >= frameDuration / 2) {
                position = originalPosition; // Return to original position
                sprite.setPosition(position); // Update the sprite's position
                currentFrame = 0; // Reset back to first frame
                elapsedTime = 0.0f; // Reset elapsed time
            }
        }

        // Update the sprite's texture rectangle based on the current frame
        updateSpriteRect();
    }

    // Draw the Eating sprite
    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

private:
    sf::Sprite sprite;       // Sprite to display the current frame of the activity
    sf::Texture texture;     // Texture for the sprite sheet
    float frameDuration;     // Duration for showing the first frame and alternating frames
    int currentFrame;        // Current frame index (0: first frame, 1: second frame, 2: third frame)
    float elapsedTime = 0.0f; // Time elapsed since the last frame switch
    bool isAnimating;        // Flag to control whether animation is active
    sf::Vector2f position;   // Current position of the sprite
    sf::Vector2f originalPosition; // Store the original position of the sprite

    // Update the sprite rectangle based on the current frame
    void updateSpriteRect() {
        // Calculate the frame size based on the sprite sheet
        int frameWidth = texture.getSize().x / 2;  // There are 2 columns (frames) in the first row
        int frameHeight = texture.getSize().y / 2; // There are 2 rows, but the second row has only 1 frame

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
    sf::RenderWindow window(sf::VideoMode(800, 600), "Eating Activity");

    // Frame limit for smooth display
    window.setFramerateLimit(60);

    // Load the sprite sheet for the "eating" activity (3 frames) with scaling
    Eating eating("Big/eating.png", 1.4f, 2.9f, 2.9f);  // Adjust frame duration and scaling

    // Start the animation
    eating.startAnimation();

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

        // Update the Eating animation
        eating.update(deltaTime);

        // Clear the window
        window.clear(sf::Color(245, 245, 220));

        // Draw the Eating
        eating.draw(window);

        // Display the window contents
        window.display();
    }

    return 0;
}
