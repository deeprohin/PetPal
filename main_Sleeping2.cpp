#include <SFML/Graphics.hpp>
#include "Sleeping.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sleeping Animation");
    window.setFramerateLimit(60);

    Sleeping sleeping("Big/Sleeping.png", 1.4f, 2.9f, 2.9f);
    sleeping.startAnimation();

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        sleeping.update(deltaTime);

        window.clear(sf::Color(245, 245, 220));

        sleeping.draw(window);

        window.display();
    }

    return 0;
}
