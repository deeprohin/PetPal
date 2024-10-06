#include <SFML/Graphics.hpp>
#include "Big2Medicine.cpp"

int main() {
    // Create a window (800x600)
    sf::RenderWindow window(sf::VideoMode(800, 600), "Medicine Animation");

    // Frame limit for smooth display
    window.setFramerateLimit(60);

    // Load the sprite sheet for the "Medicine" activity (2 frames) with scaling
    Medicine medicine("Big2/Eating/spritesheet.png", 1.4f, 2.9f, 2.9f);  // Adjust frame duration and scaling

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
