#include <SFML/Graphics.hpp>
#include "Sleeping.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sleeping Animation");
    window.setFramerateLimit(60);

    // Load the sprite sheet for the "sleeping" activity with scaling factors
    Sleeping sleeping("Small/Sleeping.png", 0.8f, 2.2f, 2.2f);
    sleeping.startAnimation();

    sf::Clock clock; // Clock to track time

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
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
