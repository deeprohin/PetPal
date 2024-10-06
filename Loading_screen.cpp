#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main()
{
    // Create a video mode object and window (1920x1080)
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Loading Screen");

    // Set the frame rate limit
    window.setFramerateLimit(60);

    // Cream/beige color (RGB values)
    sf::Color beige(245, 245, 220);

    // Load the cat sprite texture
    sf::Texture catTexture;
    if (!catTexture.loadFromFile("Images/cat.png"))
    {
        std::cerr << "Error loading cat.png" << std::endl;
        return -1;
    }

    // Create a sprite from the texture
    sf::Sprite catSprite;
    catSprite.setTexture(catTexture);

    // Position the cat sprite at the center of the screen
    sf::FloatRect spriteBounds = catSprite.getLocalBounds();
    catSprite.setOrigin(spriteBounds.width / 2, spriteBounds.height / 2);
    catSprite.setPosition(1920 / 2, 1080 / 2);

    // Load the theme song
    sf::Music themeMusic;
    if (!themeMusic.openFromFile("Audio/Rapid_fire.ogg")) // You can also use theme.wav
    {
        std::cerr << "Error loading theme music" << std::endl;
        return -1;
    }

    // Play the theme song in a loop
    themeMusic.setLoop(true);
    themeMusic.play();

    // Game loop
    while (window.isOpen())
    {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window with the beige background
        window.clear(beige);

        // Draw the cat sprite
        window.draw(catSprite);

        // Display the current frame
        window.display();
    }

    return 0;
}
