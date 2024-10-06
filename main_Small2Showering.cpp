#include <SFML/Graphics.hpp>
#include "Small2Showering.cpp"

int main() {
    // Create a window (800x600)
    sf::RenderWindow window(sf::VideoMode(800, 600), "Showering");

    // Frame limit for smooth display
    window.setFramerateLimit(60);

    // Load the sprite sheet and set up Shower
    Shower Shower("Small2/Showering/spritesheet.png", 0.8f, 2.0f, 2.0f);  // Adjust scale and frame duration as needed

    // Start the Shower
    Shower.startAnimation();

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

        // Update the Shower
        Shower.update(deltaTime);

        // Clear the window
        window.clear(sf::Color(245, 245, 220));  // Optionally change the color for better visibility

        // Draw the Shower
        Shower.draw(window);

        // Display the window contents
        window.display();
    }

    return 0;
}
