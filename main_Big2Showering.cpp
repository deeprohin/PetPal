#include <SFML/Graphics.hpp>
#include "Big2Showering.cpp"

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
