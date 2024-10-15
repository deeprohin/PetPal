#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

// Base class for handling eating animations
class Eating {
 public:
  // Constructor initializes the sprite sheet and animation parameters
  Eating(const std::string& spriteSheetPath, float frameDuration, float scaleX,
         float scaleY)
      : frameDuration_eating(frameDuration),
        elapsedTime_eating(0.0f),
        currentFrame_eating(0),
        isAnimating_eating(false) {};

  // Default constructor
  Eating() {}

  // Starts the eating animation
  virtual void startAnimation_eating() = 0;

  // Updates the animation based on the time passed
  virtual void update_eating(float deltaTime) = 0;

  // Draws the current frame of the eating animation
  virtual void draw_eating(sf::RenderWindow& window) = 0;

  // Sprite for the eating animation
  sf::Sprite sprite_eating;

  // Texture for the sprite
  sf::Texture texture_eating;

  // Duration for each frame of the animation
  float frameDuration_eating;

  // Current frame index
  int currentFrame_eating;

  // Time elapsed since the last frame change
  float elapsedTime_eating;

  // Flag to check if the animation is active
  bool isAnimating_eating;

  // Position of the sprite
  sf::Vector2f position_eating;

  // Original position to return to
  sf::Vector2f originalPosition_eating;

  // Updates the sprite rectangle based on the current frame
  virtual void updateSpriteRect_eating() = 0;

  // Virtual destructor
  virtual ~Eating() {}
};


