#pragma once
#include <SFML/Graphics.hpp>

class Animation {
 public:
  Animation(sf::Texture* texture, sf::Vector2u image_count, float switch_time);
  ~Animation();

  void update(int row, float delta_time);

  // getter for uv_rect
  const sf::IntRect& getUVRect() const { return uv_rect; }
  sf::IntRect uv_rect;         // rectangle to define the area of the texture
  sf::Vector2u image_count;    // number of images in the sprite sheet
  float total_time;            // time accumulated for animation
  float switch_time;           // time to switch to the next image
  sf::Vector2u current_image;  // current image being displayed

 private:
};
