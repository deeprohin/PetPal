#include <SFML/Graphics.hpp>
#include "Medicine.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Medicine Animation");
    window.setFramerateLimit(60);

    Medicine medicine("Small/Eating.png", 0.8f, 2.2f, 2.2f);

    medicine.startAnimation();

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        medicine.update(deltaTime);

        window.clear(sf::Color(245, 245, 220));
        medicine.draw(window);
        window.display();
    }

    return 0;
}
