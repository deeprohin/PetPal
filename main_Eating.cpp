#include <SFML/Graphics.hpp>
#include "Eating.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Eating Activity");
    window.setFramerateLimit(60);

    Eating eat("Small/eating.png", 0.8f, 2.2f, 2.2f);

    eat.startAnimation();

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        eat.update(deltaTime);

        window.clear(sf::Color(245, 245, 220));
        eat.draw(window);
        window.display();
    }

    return 0;
}
