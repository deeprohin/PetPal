#ifndef ADULT_Ghost_H
#define ADULT_Ghost_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Eating.h"
#include "Medicine.h"
#include "Shower.h"
#include "Sleeping.h"
#include "ghost.h"
#include "pet_stats.h"

// adult ghost class inheritting publically from ghsot parent class and
// shower,eating,sleeping and medicine class
class adult_ghost : public Shower,
                    public Eating,
                    public Sleeping,
                    public Medicine,
                    public ghost {
 public:
  // constructor to load sprite sheet
  adult_ghost(const std::string& spriteSheetPath, float frameDuration,
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
    // setting up initial textures
    sprite_shower.setTexture(texture_shower);
    sprite_eating.setTexture(texture_eating);
    sprite_sleeping.setTexture(texture_eating);
    sprite_medicine.setTexture(texture_eating);
    // scaling the textures
    sprite_shower.setScale(scaleX, scaleY);
    sprite_eating.setScale(scaleX, scaleY);
    sprite_sleeping.setScale(scaleX, scaleY);
    sprite_medicine.scale(scaleX, scaleY);
    // updating functions for updating tecture for the initial frames
    updateSpriteRect_shower();
    updateSpriteRect_eating();
    updateSpriteRect_sleeping();
    updateSpriteRect_medicine();
  }
  // animation for adult_ghost to start showering
  void startAnimation_shower() override {
    isAnimating_shower = true;
    currentFrame_shower = 0;    // resetting to the first frame
    elapsedTime_shower = 0.0f;  // resetting the time
    position_shower.x = 600.f;  // deciding upon the position
    position_shower.y = 350.f;
    originalPosition_shower = position_shower;
    sprite_shower.setPosition(
        position_shower);  // setting the sprite's position
  }

  void update_shower(float deltaTime) override {
    if (!isAnimating_shower) return;  // not updating if it isnt animating
    // accumulating time
    elapsedTime_shower += deltaTime;

    // switching frames based on how much time has passed
    if (elapsedTime_shower >= frameDuration_shower) {
      currentFrame_shower =
          (currentFrame_shower + 1) % 4;  // looping between all the frames
      elapsedTime_shower = 0.0f;          // resetting the time
    }
    updateSpriteRect_shower();  // calling the update function
  }
  // drawing the showering animation
  void draw_shower(sf::RenderWindow& window) override {
    window.draw(sprite_shower);
  }
  // function to udpate the showering sprite
  void updateSpriteRect_shower() override {
    // calculating the size of the frames
    int frameWidth = texture_shower.getSize().x / 2;
    int frameHeight = texture_shower.getSize().y / 2;

    // getting the x and y cooridnate of the top left corner of the frame in the
    // spritesheet
    int frameX = (currentFrame_shower % 2) * frameWidth;
    int frameY = (currentFrame_shower / 2) * frameHeight;

    // setting the texture for the spirte
    sprite_shower.setTextureRect(
        sf::IntRect(frameX, frameY, frameWidth, frameHeight));
    // printing out the coordinates for the frame
    std::cout << "Frame " << currentFrame_shower << ": (X: " << frameX
              << ", Y: " << frameY << ")" << std::endl;
  }
  // fnction to satrt animation for sleeping of adult_ghost
  void startAnimation_sleeping() override {
    isAnimating_sleeping = true;
    currentFrame_sleeping = 0;  // resettting everything
    elapsedTime_sleeping = 0.0f;

    position_sleeping.x = 600.f;  // decding on the position
    position_sleeping.y = 350.f;
    sprite_sleeping.setPosition(position_sleeping);  // setting the position
  }

  void update_sleeping(float deltaTime) override {
    if (!isAnimating_sleeping)
      return;  // not updating if the animtaion is not running

    elapsedTime_sleeping += deltaTime;

    // showing frames for a specific duration
    if (elapsedTime_sleeping >= frameDuration_sleeping) {
      currentFrame_sleeping = (currentFrame_sleeping + 1) % 3;
      elapsedTime_sleeping = 0.0f;  // resetting the time here
    }

    // updating the sprite teture based on what frame it is
    updateSpriteRect_sleeping();
  }
  // drwaing the sleeping animation
  void draw_sleeping(sf::RenderWindow& window) override {
    window.draw(sprite_sleeping);
  }

  void updateSpriteRect_sleeping() override {
    // calculating the size of the frame based on the spritesheet
    int frameWidth = texture_sleeping.getSize().x / 2;
    int frameHeight = texture_sleeping.getSize().y / 2;

    // x and y coordinates of the topleft corner of the frame in the sprite
    // sheet
    int frameX = 0;
    int frameY = 0;

    // deciding which frame to use based on what the current frame is
    switch (currentFrame_sleeping) {
      case 0:
        frameX = 0;
        frameY = 0;
        break;
      case 1:
        frameX = frameWidth;
        frameY = 0;
        break;
      case 2:
        frameX = 0;
        frameY = frameHeight;
        break;
    }
    // setting texture for the sprite
    sprite_sleeping.setTextureRect(
        sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    // printing coorindates of the frame
    std::cout << "Frame " << currentFrame_sleeping << ": (X: " << frameX
              << ", Y: " << frameY << ")" << std::endl;
  }
  // function to start the eating function
  void startAnimation_eating() override {
    // deciding upon the positions and initialising the time and the frame
    isAnimating_eating = true;
    currentFrame_eating = 0;
    elapsedTime_eating = 0.0f;
    position_eating.x = 600.f;
    position_eating.y = 350.f;
    originalPosition_eating = position_eating;
    sprite_eating.setPosition(position_eating);
  }
  // fucntion to udpate the eating animation
  void update_eating(float deltaTime) override {
    if (!isAnimating_eating) return;

    elapsedTime_eating += deltaTime;

    // cycling between frames for  a specific duration of time
    if (currentFrame_eating == 0) {
      if (elapsedTime_eating >= frameDuration_eating) {
        currentFrame_eating = 1;
        position_eating.x -= 3;
        sprite_eating.setPosition(
            position_eating);       // updating postion of the sprite
        elapsedTime_eating = 0.0f;  // resetting the time
      }
    } else if (currentFrame_eating == 1) {
      if (elapsedTime_eating >= frameDuration_eating / 2) {
        currentFrame_eating = 2;    // moving onto third frame
        elapsedTime_eating = 0.0f;  // resetting the elapsed time
      }
    } else if (currentFrame_eating == 2) {
      // returning to original position
      if (elapsedTime_eating >= frameDuration_eating / 2) {
        position_eating = originalPosition_eating;
        sprite_eating.setPosition(
            position_eating);  // udpatinf the position of the sprite
        currentFrame_eating = 0;
        elapsedTime_eating = 0.0f;
      }
    }

    // updating the spirte based on what the current frame is
    updateSpriteRect_eating();
  }

  // function to drwa the eating animation
  void draw_eating(sf::RenderWindow& window) override {
    window.draw(sprite_eating);
  }
  // fucntion to update the eating sprite
  void updateSpriteRect_eating() override {
    // calculatinf the frame size based on what the size of the spritesheet is
    int frameWidth = texture_eating.getSize().x / 2;
    int frameHeight = texture_eating.getSize().y / 2;

    // x and y coordinates of the top left corner of the frame in the
    // spritesheet
    int frameX = 0;
    int frameY = 0;

    // Determining which frame to use based on currentFrame

    switch (currentFrame_eating) {
      case 0:
        frameX = 0;
        frameY = 0;
        break;
      case 1:
        frameX = frameWidth;
        frameY = 0;
        break;
      case 2:
        frameX = 0;
        frameY = frameHeight;
        break;
    }
    // Setting the texture for the sprite
    sprite_eating.setTextureRect(
        sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    // printing out the coordinates of the frame
    std::cout << "Frame " << currentFrame_eating << ": (X: " << frameX
              << ", Y: " << frameY << ")" << std::endl;
  }
  // function to start thr animation for eating teh medicine
  void startAnimation_medicine() override {
    // deciding on the position for the medicine
    isAnimating_medicine = true;
    currentFrame_medicine = 0;
    elapsedTime_medicine =
        0.0f;  // resetting the time and initialising the current frame
    position_medicine.x = 600.f;
    position_medicine.y = 350.f;
    originalPosition_medicine = position_medicine;
    sprite_medicine.setPosition(position_medicine);
  }

  // function to update the medicine animation
  void update_medicine(float deltaTime) override {
    if (!isAnimating_medicine) return;

    elapsedTime_medicine += deltaTime;

    // displaying each frame for some decided duration
    if (elapsedTime_medicine >= frameDuration_medicine) {
      currentFrame_medicine =
          (currentFrame_medicine + 1) % 2;  // swwitching between the frames
      elapsedTime_medicine = 0.0f;
    }

    // updating the sprite texture based on what the current frame is
    updateSpriteRect_medicine();
  }
  // function to draw the medicine
  void draw_medicine(sf::RenderWindow& window) override {
    window.draw(sprite_medicine);
  }
  // function to update hte sprite for medicine
  void updateSpriteRect_medicine() override {
    // Frame dimensions based on the sprite sheet
    int frameWidth = 32;
    int frameHeight = 32;

    // Determining which frame to use based on the current frame index
    int frameX = 0;
    int frameY = currentFrame_medicine *
                 frameHeight;  // Determine Y position based on current frame

    // Set the texture rectangle for the sprite
    sprite_medicine.setTextureRect(
        sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    // printing out frame coorinates for the purpose of debugging
    std::cout << "Frame rect set: (X: " << frameX << ", Y: " << frameY
              << ", Width: " << frameWidth << ", Height: " << frameHeight << ")"
              << std::endl;
  }
};
#endif