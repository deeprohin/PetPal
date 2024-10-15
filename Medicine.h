#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

// Base class for handling medicine animations
class Medicine {
 public:
  // Constructor: Initializes the medicine object with the sprite sheet path,
  // frame duration, and optional scale factors
  Medicine(const std::string& spriteSheetPath, float frameDuration,
           float scaleX = 1.0f, float scaleY = 1.0f)
      : frameDuration_medicine(frameDuration),  // How long each frame lasts
        elapsedTime_medicine(0.0f),  // Time passed since the last frame
        currentFrame_medicine(0),    // Currently displayed frame index
        isAnimating_medicine(false) {
  }  // Whether the animation is currently running

  // Starts the animation
  virtual void startAnimation_medicine() = 0;

  // Updates the animation state based on the time elapsed since the last update
  virtual void update_medicine(float deltaTime) = 0;

  // Draws the medicine sprite on the provided window
  virtual void draw_medicine(sf::RenderWindow& window) = 0;

  // The sprite representing the medicine in the game
  sf::Sprite sprite_medicine;

  // Texture for the medicine sprite
  sf::Texture texture_medicine;

  // Duration of each frame in the animation
  float frameDuration_medicine;

  // Index of the current frame being displayed
  int currentFrame_medicine;

  // Time elapsed since the last frame update
  float elapsedTime_medicine;

  // Flag indicating if the animation is currently running
  bool isAnimating_medicine;

  // Current position of the medicine sprite in the game world
  sf::Vector2f position_medicine;

  // Original position where the medicine sprite was initialized
  sf::Vector2f originalPosition_medicine;

  // Updates the sprite rectangle for animation
  virtual void updateSpriteRect_medicine() = 0;
};
