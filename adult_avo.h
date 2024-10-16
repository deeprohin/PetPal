#ifndef ADULT_AVO_H
#define ADULT_AVO_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Eating.h"
#include "Medicine.h"
#include "Shower.h"
#include "Sleeping.h"
#include "avo.h"
#include "pet_stats.h"


// creating adult avo class which inherits publicaly from avo,
// shower,eating,sleeping,medicine
class adult_avo : public Shower,
                  public Eating,
                  public Sleeping,
                  public Medicine,
                  public avo {
 public:
  // construcot for initialising and laoding the sprite sheets for all the
  // activities
  adult_avo(const std::string& spriteSheetPath, float frameDuration,
            float scaleX = 1.0f, float scaleY = 1.0f)
      : Shower(spriteSheetPath, frameDuration, scaleX, scaleY),
        Eating(spriteSheetPath, frameDuration, scaleX, scaleY),
        Sleeping(spriteSheetPath, frameDuration, scaleX, scaleY),
        Medicine(spriteSheetPath, frameDuration, scaleX, scaleY) {
    // Loading textures for the activities
    if (!texture_shower.loadFromFile(spriteSheetPath) ||
        !texture_eating.loadFromFile(spriteSheetPath) ||
        !texture_sleeping.loadFromFile(spriteSheetPath) ||
        !texture_medicine.loadFromFile(spriteSheetPath)) {
      std::cerr << "Error loading sprite sheet: " << spriteSheetPath
                << std::endl;
    }
    // Initializing the sprite with textures for different activities
    sprite_shower.setTexture(texture_shower);
    sprite_eating.setTexture(texture_eating);
    sprite_sleeping.setTexture(texture_eating);
    sprite_medicine.setTexture(texture_eating);

    // scaling the sprites
    sprite_shower.setScale(scaleX, scaleY);
    sprite_eating.setScale(scaleX, scaleY);
    sprite_sleeping.setScale(scaleX, scaleY);
    sprite_medicine.scale(scaleX, scaleY);

    // setting the texture for the initail frame of each activity
    updateSpriteRect_shower();
    updateSpriteRect_eating();
    updateSpriteRect_sleeping();
    updateSpriteRect_medicine();
  }

  adult_avo(){}
  // Starting animation for the shower activity
  void startAnimation_shower() override {
    isAnimating_shower = true;
    currentFrame_shower = 0;    // Resetting it  to the first frame
    elapsedTime_shower = 0.0f;  // Resetting the elapsed time
    position_shower.x = 600.f;  // deciding the position of the animation
    position_shower.y = 350.f;
    originalPosition_shower =
        position_shower;  // storing the original position in the
                          // originalPosition_shower variable
    sprite_shower.setPosition(
        position_shower);  // Setting the sprite's position
  }

  // Updating the shower animation based on how much time has passsed
  void update_shower(float deltaTime) override {
    if (!isAnimating_shower) return;
    // Accumulating the time passed
    elapsedTime_shower += deltaTime;

    // Switching frames based on how much time and updating the sprite texture
    if (elapsedTime_shower >= frameDuration_shower) {
      currentFrame_shower = (currentFrame_shower + 1) % 5;
      elapsedTime_shower = 0.0f;  // Resetting the elapsed time
    }
    updateSpriteRect_shower();  // updating the current frame
  }

  // Drawing the shower animation to the window
  void draw_shower(sf::RenderWindow& window) override {
    window.draw(sprite_shower);
  }

  // Updating the sprite texture based on the current shower frame
  void updateSpriteRect_shower() override {
    // Calculating frame size from sprite sheet as it contains 5 columns in the
    // first
    int frameWidth = texture_shower.getSize().x / 5;
    int frameHeight = texture_shower.getSize().y;

    // setting the x coordinate for each frame according to what the current
    // frame is
    int frameX = currentFrame_shower * frameWidth;
    int frameY = 0;  // because there is just one row of frames

    // setting the texturre for the sprite
    sprite_shower.setTextureRect(
        sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    // printing the coordiantes for tbe frame
    std::cout << "Frame " << currentFrame_shower << ": (X: " << frameX
              << ", Y: " << frameY << ")" << std::endl;
  }

  // same logic for eating animation
  void startAnimation_eating() override {
    isAnimating_eating = true;  // setting the eating animation to true
    currentFrame_eating = 0;    // resetting it to the first frame
    elapsedTime_eating = 0.0f;  // resetting time passe byd
    position_eating.x = 600.f;  // deciding the satrting position for the frames
    position_eating.y = 350.f;  // deciding on the y coordinate
    originalPosition_eating = position_eating;   // storing teh original
                                                 // positions
    sprite_eating.setPosition(position_eating);  // setting the sprite position
  }

  // updating teh eating aninmation based on how much time has passed
  void update_eating(float deltaTime) override {
    if (!isAnimating_eating) return;  // not updating if it is not animating

    // accumulating time
    elapsedTime_eating += deltaTime;

    // updating frames to move sprite in different directions
    if (currentFrame_eating == 0) {
      if (elapsedTime_eating >= frameDuration_eating) {
        currentFrame_eating = 1;  // moving onto the second frame
        position_eating.x -= 3;   // Move left by 3 units
        sprite_eating.setPosition(
            position_eating);  // setting the position based on what frame it is
        elapsedTime_eating = 0.0f;
      }
    } else if (currentFrame_eating == 1) {
      if (elapsedTime_eating >= frameDuration_eating / 2) {
        // moving onto thrid frame
        currentFrame_eating = 2;
        elapsedTime_eating = 0.0f;
      }
    } else if (currentFrame_eating == 2) {
      if (elapsedTime_eating >= frameDuration_eating / 2) {
        // moving back to original position
        position_eating = originalPosition_eating;
        sprite_eating.setPosition(position_eating);
        currentFrame_eating = 0;
        elapsedTime_eating = 0.0f;
      }
    }

    // updating the current sprite frame
    updateSpriteRect_eating();
  }

  // drawing the eating sprite to the window
  void draw_eating(sf::RenderWindow& window) override {
    window.draw(sprite_eating);
  }

  // updating the sprite texture based on what frame it is on currently
  void updateSpriteRect_eating() override {
    // Calculating frame size based on size of spritesheet
    int frameWidth = texture_eating.getSize().x / 3;
    int frameHeight = texture_eating.getSize().y;

    // setting the x coordinates
    int frameX = currentFrame_eating * frameWidth;
    int frameY = 0;

    // texture for the sprite
    sprite_eating.setTextureRect(
        sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    // printing out the coordinates of the frames
    std::cout << "Frame " << currentFrame_eating << ": (X: " << frameX
              << ", Y: " << frameY << ")" << std::endl;
  }

  void startAnimation_sleeping() override {
    isAnimating_sleeping = true;
    currentFrame_sleeping = 0;    // Reset to first frame
    elapsedTime_sleeping = 0.0f;  // Reset elapsed time

    // Center the sprite's position in the window
    position_sleeping.x = 600.f;  // Center X position
    position_sleeping.y = 350.f;  // Center Y position
    sprite_sleeping.setPosition(
        position_sleeping);  // Set the sprite's initial position
  }

  void update_sleeping(float deltaTime) override {
    if (!isAnimating_sleeping) return;  // Do not update if not animating

    // Accumulate time
    elapsedTime_sleeping += deltaTime;

    // Show each frame for a specified duration
    if (elapsedTime_sleeping >= frameDuration_sleeping) {
      currentFrame_sleeping =
          (currentFrame_sleeping + 1) % 3;  // Cycle through all 6 frames
      elapsedTime_sleeping = 0.0f;          // Reset elapsed time
    }

    // Update the sprite's texture rectangle based on the current frame
    updateSpriteRect_sleeping();
  }

  void draw_sleeping(sf::RenderWindow& window) override {
    window.draw(sprite_sleeping);
  }

  void updateSpriteRect_sleeping() override {
    // Calculate the frame size based on the sprite sheet
    int frameWidth = 32;   // There are 4 columns
    int frameHeight = 32;  // There is 1 row

    // x and y coordinates of the top-left corner of the fcrame in the sprite
    // sheet
    int frameX = 0;
    int frameY = 0;

    // Determine which frame to use based on currentFrame
    switch (currentFrame_sleeping) {
      case 0:
        frameX = 0;
        break;  // First frame
      case 1:
        frameX = 32;
        break;  // Second frame
      case 2:
        frameX = 64;
        break;  // Third frame
      case 3:
        frameX = 96;
        break;
    }
    // setting texture for the sprite
    sprite_sleeping.setTextureRect(
        sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    // printing the coordinates of the frame
    std::cout << "Frame " << currentFrame_sleeping << ": (X: " << frameX
              << ", Y: " << frameY << ")" << std::endl;
  }

  void startAnimation_medicine() override {
    isAnimating_medicine = true;
    currentFrame_medicine = 0;    // resetting to the first frame
    elapsedTime_medicine = 0.0f;  // resetting the time passed
    position_medicine.x = 600.f;  // deciding the starting position
    position_medicine.y = 350.f;  // deciding on y position
    originalPosition_medicine =
        position_medicine;  // storing the original position for the medicine
    sprite_medicine.setPosition(
        position_medicine);  // setting up initial position for the sprite
  }
  // updating the medicine
  void update_medicine(float deltaTime) override {
    if (!isAnimating_medicine) return;

    elapsedTime_medicine += deltaTime;

    // displaying each frame for decided time duration
    if (elapsedTime_medicine >= frameDuration_medicine) {
      currentFrame_medicine =
          (currentFrame_medicine + 1) % 2;  // to switch between two frames
      elapsedTime_medicine = 0.0f;
    }

    // updating the texture of the sprite based on the current frame
    updateSpriteRect_medicine();
  }

  void draw_medicine(sf::RenderWindow& window) override {
    window.draw(sprite_medicine);
  }

  void updateSpriteRect_medicine() override {
    //
    int frameWidth = 32;
    int frameHeight = 36;

    int frameX = 0;
    int frameY = 0;

    // deciding which frame to chose
    switch (currentFrame_medicine) {
      case 0:  // frame 1- row 1 nad column 1
        frameX = 0;
        frameY = 0;
        break;
        // second frame
      case 1:
        frameX = frameWidth;
        frameY = 0;
        break;
    }

    // setting texture of the sprite
    sprite_medicine.setTextureRect(
        sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    // printing out the coordinates for the frame
    std::cout << "Frame rect set: (X: " << frameX << ", Y: " << frameY
              << ", Width: " << frameWidth << ", Height: " << frameHeight << ")"
              << std::endl;
  }

  void draw_default_sprite(sf::RenderWindow& window) override{
    window.draw(sprite_shower);
  }
};
#endif
