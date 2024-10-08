#include <SFML/Graphics.hpp>
#include "Sleeping.cpp"  // Include Sleeping if needed in your project

int main()
{
    // Create a window (800x600)
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sleeping");

    // Frame limit for smooth display
    window.setFramerateLimit(60);

    // Load the sprite sheet for the "Sleeping" activity with scaling factors
    Sleeping Sleeping("Small/Sleeping.png", 0.8f, 2.2f, 2.2f);  // Adjust frame duration as needed, scaled by 2x

    // Start the Sleeping
    Sleeping.startAnimation();

    // Main game loop
    sf::Clock clock; // Clock to track time
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Get the time elapsed since the last frame
        float deltaTime = clock.restart().asSeconds();

        // Update the Sleeping Sleeping
        Sleeping.update(deltaTime);

        // Clear the window
        window.clear(sf::Color(245, 245, 220)); // Optionally change the color for better visibility

        // Draw the Sleeping sprite
        Sleeping.draw(window);

        // Display the window contents
        window.display();
    }

    return 0;
}
