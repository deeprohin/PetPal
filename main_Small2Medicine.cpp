// main.cpp
#include <SFML/Graphics.hpp>
#include "Small2Medicine.cpp"

int main() {
    // Create a window (800x600)
    sf::RenderWindow window(sf::VideoMode(800, 600), "Medicine Example");

    // Frame limit for smooth display
    window.setFramerateLimit(60);

    // Load the sprite sheet for the Medicine with scaling factors
    Medicine Medicine("Small2/medications/spritesheet.png", 0.8f, 2.2f, 2.2f);  // Adjust path and scaling as needed

    // Start the Medicine
    Medicine.startAnimation();

    // Main game loop
    sf::Clock clock;  // Clock to track time
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Get the time elapsed since the last frame
        float deltaTime = clock.restart().asSeconds();

        // Update the Medicine
        Medicine.update(deltaTime);

        // Clear the window
        window.clear(sf::Color(245, 245, 220));  // Optional: Change the background color for visibility

        // Draw the animated sprite
        Medicine.draw(window);

        // Display the window contents
        window.display();
    }

    return 0;
}
