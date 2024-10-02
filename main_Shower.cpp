#include <SFML/Graphics.hpp>
#include "Shower.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Shower Animation");
    window.setFramerateLimit(60);

    // Load the sprite sheet for the "shower" activity with scaling factors
    Shower shower("Small/Shower.png", 0.8f, 2.2f, 2.2f);

    shower.startAnimation();

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        shower.update(deltaTime);

        window.clear(sf::Color(245, 245, 220));
        shower.draw(window);
        window.display();
    }

    return 0;
}
