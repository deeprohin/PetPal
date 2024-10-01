#include <SFML/Graphics.hpp>
#include <iostream>

class Medicine {
public:
    // Constructor to load the sprite sheet for an activity with scaling
    Medicine(const std::string& spriteSheetPath, float frameDuration, float scaleX = 1.0f, float scaleY = 1.0f)
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

    // Start the animation
    void startAnimation() {
        isAnimating = true;
        currentFrame = 0; // Reset to first frame
        elapsedTime = 0.0f; // Reset elapsed time
    }

    // Update the animation based on the time elapsed
    void update(float deltaTime) {
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
    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
        // Debugging output to check sprite position
        std::cout << "Drawing sprite at: (" << sprite.getPosition().x << ", " << sprite.getPosition().y << ")" << std::endl;
    }

private:
    sf::Sprite sprite;       // Sprite to display the current frame of the activity
    sf::Texture texture;     // Texture for the sprite sheet
    float frameDuration;     // Duration for showing each frame
    int currentFrame;        // Current frame index (0 or 1)
    float elapsedTime = 0.0f; // Time elapsed since the last frame switch
    bool isAnimating;        // Flag to control whether animation is active

    // Update the sprite rectangle based on the current frame
    void updateSpriteRect() {
        // Calculate the frame size based on the sprite sheet
        int frameWidth = 32;  // Each frame width
        int frameHeight = 32; // Each frame height

        // x and y coordinates of the top-left corner of the frame in the sprite sheet
        int frameX = 0;
        int frameY = 0;

        // Determine which frame to use based on currentFrame
        switch (currentFrame) {
            case 0: // First frame
                frameX = 0;
                frameY = 0;
                break;
            case 1: // Second frame
                frameX = 0; // No horizontal move as there's only one column
                frameY = frameHeight; // Move down to the second frame
                break;
        }

        // Set the texture rectangle for the sprite
        sprite.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));

        // Debugging output to check the frame rect
        std::cout << "Frame rect set: (X: " << frameX << ", Y: " << frameY << ", Width: " << frameWidth << ", Height: " << frameHeight << ")" << std::endl;
    }
};

int main() {
    // Create a window (800x600)
    sf::RenderWindow window(sf::VideoMode(800, 600), "Medicine Animation");

    // Frame limit for smooth display
    window.setFramerateLimit(60);

    // Load the sprite sheet for the "Medicine" activity with scaling
    Medicine medicine("Big/Eating.png", 1.4f, 2.9f, 2.9f);  // Adjust frame duration and scaling

    // Start the animation
    medicine.startAnimation();

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

        // Update the Medicine animation
        medicine.update(deltaTime);

        // Clear the window
        window.clear(sf::Color(245, 245, 220)); // Optionally change the color for better visibility

        // Draw the Medicine sprite
        medicine.draw(window);

        // Display the window contents
        window.display();
    }

    return 0;
}
