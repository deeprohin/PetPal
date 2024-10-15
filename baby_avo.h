#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Eating.h"
#include "Medicine.h"
#include "Shower.h"
#include "Sleeping.h"
#include "avo.h"
#include "pet_stats.h"
// baby avo class inheriting publically from avo,
// shower,eating,sleeping,medicine class
class baby_avo : public Shower,
                 public Eating,
                 public Sleeping,
                 public Medicine,
                 public avo {
 public:
  // constructor with paramteres
  baby_avo(const std::string& spriteSheetPath, float frameDuration,
           float scaleX = 1.0f, float scaleY = 1.0f)
      : Shower(spriteSheetPath, frameDuration, scaleX, scaleY),
        Eating(spriteSheetPath, frameDuration, scaleX, scaleY),
        Sleeping(spriteSheetPath, frameDuration, scaleX, scaleY),
        Medicine(spriteSheetPath, frameDuration, scaleX, scaleY) {
    if (!texture_shower.loadFromFile(spriteSheetPath) ||
        !texture_eating.loadFromFile(spriteSheetPath) ||
        !texture_sleeping.loadFromFile(spriteSheetPath) ||
        !texture_medicine.loadFromFile(spriteSheetPath)) {
      std::cerr << "Error loading sprite sheet: " << spriteSheetPath
                << std::endl;
    }
    // setting up the initial sprite
    sprite_shower.setTexture(texture_shower);
    sprite_eating.setTexture(texture_eating);
    sprite_sleeping.setTexture(texture_eating);
    sprite_medicine.setTexture(texture_eating);
    // applying scaling to the sprite
    sprite_shower.setScale(scaleX, scaleY);
    sprite_eating.setScale(scaleX, scaleY);
    sprite_sleeping.setScale(scaleX, scaleY);
    sprite_medicine.scale(scaleX, scaleY);
    // updating the texture rectangle for the initial frame
    updateSpriteRect_shower();
    updateSpriteRect_eating();
    updateSpriteRect_sleeping();
    updateSpriteRect_medicine();
  }
  // function to start the animation for showering
  void startAnimation_shower() override {
    isAnimating_shower = true;
    currentFrame_shower = 0;    // resetting the first frame
    elapsedTime_shower = 0.0f;  // resetting the elapsed time
    position_shower.x = 600.f;
    position_shower.y = 350.f;
    originalPosition_shower = position_shower;
  }

  void update_shower(float deltaTime) override {
    if (!isAnimating_shower) return;  // not udpating when it is not animating

    elapsedTime_shower += deltaTime;

    // switching frames based on how much time is elapsed
    if (elapsedTime_shower >= frameDuration_shower) {
      currentFrame_shower =
          (currentFrame_shower + 1) % 5;  // looping between the frames
      elapsedTime_shower = 0.0f;          // resetting the elapsed time
    }
    // updating the showering sprite
    updateSpriteRect_shower();
  }
  // drawing the shower animation
  void draw_shower(sf::RenderWindow& window) override {
    window.draw(sprite_shower);
  }
  // function to update hte showering sprite
  void updateSpriteRect_shower() override {
    // calculating size of the frame based on size of the spritesheet
    int frameWidth = texture_shower.getSize().x / 5;
    int frameHeight = texture_shower.getSize().y;
    // x and y coordinates for the first frame in the spritesheet
    int frameX = 0;
    int frameY = 0;

    // determining which frame to use based on currentFrame
    switch (currentFrame_shower) {
      case 0:
        frameX = 0;
        break;
      case 1:
        frameX = frameWidth;
        break;
      case 2:
        frameX = 2 * frameWidth;
        break;
      case 3:
        frameX = 3 * frameWidth;
        break;
      case 4:
        frameX = 4 * frameWidth;
        break;
    }
    // settting the texture rectangle for the sprite
    sprite_shower.setTextureRect(
        sf::IntRect(frameX, frameY, frameWidth, frameHeight));
    // printing the frame coordinates
    std::cout << "Frame " << currentFrame_shower << ": (X: " << frameX
              << ", Y: " << frameY << ")" << std::endl;
  }
  // function to start the animation for sleeping
  void startAnimation_sleeping() override {
    isAnimating_sleeping = true;
    currentFrame_sleeping = 0;    // resetting to the first frame
    elapsedTime_sleeping = 0.0f;  // resetting teh elapsed time

    // centering the sprite position in the window
    position_sleeping.x = 600.f;
    position_sleeping.y = 350.f;
    sprite_sleeping.setPosition(
        position_sleeping);  // setting the initial position
  }

  void update_sleeping(float deltaTime) override {
    if (!isAnimating_sleeping)
      return;  // not udpaitng if the animation isnt running

    elapsedTime_sleeping += deltaTime;

    // disaplying each frame for a specified duration
    if (elapsedTime_sleeping >= frameDuration_sleeping) {
      currentFrame_sleeping = (currentFrame_sleeping + 1) %
                              3;  // cycling 6 times between all frames
      elapsedTime_sleeping = 0.0f;
    }

    // udpating the sprite texture based on the current frame
    updateSpriteRect_sleeping();
  }
  // function to draw the sleeping animation
  void draw_sleeping(sf::RenderWindow& window) override {
    window.draw(sprite_sleeping);
  }
  // function to udpate the sprite for sleeping animation
  void updateSpriteRect_sleeping() override {
    // calculating the frame size based on the sprite sheet
    int frameWidth = texture_sleeping.getSize().x / 3;
    int frameHeight = texture_sleeping.getSize().y;

    // x and y coorindates of the first frame of the spritesheet
    int frameX = 0;
    int frameY = 0;

    // determining which frame to use based on currentFrame
    switch (currentFrame_sleeping) {
      case 0:  // 1st frame
        frameX = 0;
        frameY = 0;
        break;
      case 1:  // 2nd frame
        frameX = frameWidth;
        frameY = 0;
        break;
      case 2:
        frameX = frameWidth * 2;
        frameY = 0;
        break;
    }
    // setting the texture rectangle for the sprite
    sprite_sleeping.setTextureRect(
        sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    // printing the frame coordinates
    std::cout << "Frame " << currentFrame_sleeping << ": (X: " << frameX
              << ", Y: " << frameY << ")" << std::endl;
  }
  // function to start the animation for medicine
  void startAnimation_medicine() override {
    isAnimating_medicine = true;
    currentFrame_medicine = 0;
    elapsedTime_medicine = 0.0f;
    position_medicine.x = 600.f;
    position_medicine.y = 350.f;
    originalPosition_medicine = position_medicine;
    sprite_medicine.setPosition(position_medicine);
  }

  // function to udpate the animation for medicine
  void update_medicine(float deltaTime) override {
    if (!isAnimating_medicine) return;

    elapsedTime_medicine += deltaTime;

    // showing each frame for a specified duration
    if (elapsedTime_medicine >= frameDuration_medicine) {
      currentFrame_medicine =
          (currentFrame_medicine + 1) % 2;  // switching between 2 frames
      elapsedTime_medicine = 0.0f;
    }

    // updating the sprite texture based on what the current frame is
    updateSpriteRect_medicine();
  }
  // function to draw the medicine animation
  void draw_medicine(sf::RenderWindow& window) override {
    window.draw(sprite_medicine);
  }
  // function to update the medicine sprite
  void updateSpriteRect_medicine() override {
    // calculating frame dimensions based on the sprite sheet
    int frameWidth = 32;
    int frameHeight = 32;

    // determining which frame to use based on the current frame index
    int frameX = (currentFrame_medicine == 0) ? 0 : frameWidth;
    int frameY = 0;  // there is single row so y is 0

    // setting the texture rectangle for the sprite
    sprite_medicine.setTextureRect(
        sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    // debugging output to check the frame rect
    std::cout << "Frame rect set: (X: " << frameX << ", Y: " << frameY
              << ", Width: " << frameWidth << ", Height: " << frameHeight << ")"
              << std::endl;
  }
  // function to start the animation for eating
  void startAnimation_eating() override {
    isAnimating_eating = true;
    currentFrame_eating = 0;
    elapsedTime_eating = 0.0f;
    position_eating.x = 600.f;
    position_eating.y = 350.f;
    originalPosition_eating = position_eating;
    sprite_eating.setPosition(
        position_eating);  // setting the initial position for the sprite
  }
  // function to udpate the eating animation
  void update_eating(float deltaTime) override {
    if (!isAnimating_eating) return;

    elapsedTime_eating += deltaTime;

    // shwoing the first frame for a specified duration, then alternate frames
    if (currentFrame_eating == 0) {
      // staying on the first frame for the duration
      if (elapsedTime_eating >= frameDuration_eating) {
        currentFrame_eating = 1;
        position_eating.x -= 3;
        sprite_eating.setPosition(position_eating);
        elapsedTime_eating = 0.0f;
      }
    } else if (currentFrame_eating == 1) {
      // staying on the second frame for a short duration before returning
      if (elapsedTime_eating >= frameDuration_eating / 2) {
        currentFrame_eating = 2;    // moving to third frame
        elapsedTime_eating = 0.0f;  // resetting time
      }
    } else if (currentFrame_eating == 2) {
      // returning to original position
      if (elapsedTime_eating >= frameDuration_eating / 2) {
        position_eating = originalPosition_eating;
        sprite_eating.setPosition(position_eating);
        currentFrame_eating = 0;  // resetting to first frame
        elapsedTime_eating = 0.0f;
      }
    }

    // udpating the sprite texture based on the current frame
    updateSpriteRect_eating();
  }

  // function to draw the eating function
  void draw_eating(sf::RenderWindow& window) override {
    window.draw(sprite_eating);
  }
  // function to udpate hte eating sprite
  void updateSpriteRect_eating() override {
    // calculating the frame size based on the sprite sheet
    int frameWidth = texture_eating.getSize().x / 3;
    int frameHeight = texture_eating.getSize().y;

    // x and y coordinate of the top frame
    int frameX = 0;
    int frameY = 0;

    // determining which frame to use based on currentFrame
    switch (currentFrame_eating) {
      case 0:
        frameX = 0;
        break;
      case 1:
        frameX = frameWidth;
        break;
      case 2:
        frameX = 2 * frameWidth;
        break;
    }

    // settingg the texture  for the sprite
    sprite_eating.setTextureRect(
        sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    // printing out the coordinates for the frames
    std::cout << "Frame " << currentFrame_eating << ": (X: " << frameX
              << ", Y: " << frameY << ")" << std::endl;
  }
};