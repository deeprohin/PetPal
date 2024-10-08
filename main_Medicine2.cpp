// main.cpp
#include <SFML/Graphics.hpp>
#include "Medicine2.cpp"

int main() {
    // Create a window for the application (800x600 pixels)
    sf::RenderWindow window(sf::VideoMode(800, 600), "Medicine");

    // Set the framerate to 60 FPS for smooth animation
    window.setFramerateLimit(60);

    // Create the Medicine object, load the sprite sheet, and specify animation parameters
    Medicine medicine("Big/Eating.png", 1.4f, 2.9f, 2.9f);  // Sprite sheet, frame duration, and scale

    // Start the animation
    medicine.startAnimation();

    // Clock object to track time between frames
    sf::Clock clock;

    // Main loop that runs while the window is open
    while (window.isOpen()) {
        // Handle window events (e.g., close window)
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Get the time elapsed since the last frame
        float deltaTime = clock.restart().asSeconds();

        // Update the Medicine animation based on the time passed
        medicine.update(deltaTime);

        // Clear the window before drawing the next frame
        window.clear(sf::Color(245, 245, 220));  // Light beige background

        // Draw the Medicine animation
        medicine.draw(window);

        // Display the current frame in the window
        window.display();
    }

    return 0;
}
