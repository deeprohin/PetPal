#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation {
public:
    Animation(sf::Texture* texture, sf::Vector2u image_count, float switch_time);
    ~Animation();

    void update(int row, float delta_time);

    // Getter for uv_rect
    const sf::IntRect& getUVRect() const { return uv_rect; }
    sf::IntRect uv_rect;  // Rectangle to define the area of the texture
    sf::Vector2u image_count; // Number of images in the sprite sheet
    float total_time;     // Time accumulated for animation
    float switch_time;    // Time to switch to the next image
    sf::Vector2u current_image; // Current image being displayed

private:

};

#endif // ANIMATION_H
