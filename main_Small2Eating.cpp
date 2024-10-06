// main.cpp
#include <SFML/Graphics.hpp>
#include "Small2Eating.cpp"

int main() {
    // Create an SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Eating Activity");

    // Set frame limit for smooth Eating
    window.setFramerateLimit(60);

    // Load sprite sheet and set scaling and frame duration
    Eating Eating("Small2/Eating/spritesheet.png", 0.8f, 2.2f, 2.2f);

    // Start Eating
    Eating.startAnimation();

    // Main game loop
    sf::Clock clock;  // Clock for measuring elapsed time
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Get the elapsed time since the last frame
        float deltaTime = clock.restart().asSeconds();

        // Update the Eating object
        Eating.update(deltaTime);

        // Clear the window
        window.clear(sf::Color(245, 245, 220));

        // Draw the Eating sprite
        Eating.draw(window);

        // Display the window contents
        window.display();
    }

    return 0;
}
