#ifndef MEDICINE_H
#define MEDICINE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Medicine {
 public:
  // Constructor to initialize the medicine object with sprite sheet path, frame
  // duration, and optional scale factors
  Medicine(const std::string& spriteSheetPath, float frameDuration,
           float scaleX = 1.0f, float scaleY = 1.0f)
      : frameDuration_medicine(
            frameDuration),          // Duration for each frame in the animation
        elapsedTime_medicine(0.0f),  // Time elapsed since the last frame update
        currentFrame_medicine(0),    // Current frame being displayed
        isAnimating_medicine(false) {
  }  // Flag to indicate if the animation is active

  // Pure virtual function to start the animation
  virtual void startAnimation_medicine() = 0;

  // Pure virtual function to update the animation state based on delta time

  virtual void update_medicine(float deltaTime) = 0;

  // Pure virtual function to draw the medicine sprite on the window (must be
  // implemented in derived classes)
  virtual void draw_medicine(sf::RenderWindow& window) = 0;

  sf::Sprite sprite_medicine;    // Sprite to represent the medicine in the game
  sf::Texture texture_medicine;  // Texture for the medicine sprite
  float frameDuration_medicine;  // Duration of each frame in the animation
  int currentFrame_medicine;     // Index of the current frame
  float elapsedTime_medicine;    // Time elapsed for the current frame
  bool isAnimating_medicine;     // Flag to check if the animation is running
  sf::Vector2f position_medicine;  // Current position of the medicine sprite
  sf::Vector2f
      originalPosition_medicine;  // Original position of the medicine sprite

  // Pure virtual function to update the sprite rectangle for animation (must be
  // implemented in derived classes)
  virtual void updateSpriteRect_medicine() = 0;
};

#endif  // MEDICINE_H
