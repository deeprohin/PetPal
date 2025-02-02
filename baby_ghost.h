#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Eating.h"
#include "Medicine.h"
#include "Shower.h"
#include "Sleeping.h"
#include "ghost.h"
#include "pet_stats.h"


class baby_ghost : public Shower,public Eating,public Sleeping,public Medicine,public avo{
public:
    baby_ghost(const std::string& spriteSheetPath, float frameDuration, float scaleX = 1.0f, float scaleY = 1.0f) :Shower(spriteSheetPath, frameDuration, scaleX, scaleY),Eating(spriteSheetPath, frameDuration, scaleX, scaleY),Sleeping(spriteSheetPath, frameDuration, scaleX, scaleY),Medicine(spriteSheetPath, frameDuration, scaleX, scaleY){
        if (!texture_shower.loadFromFile(spriteSheetPath)||!texture_eating.loadFromFile(spriteSheetPath)||!texture_sleeping.loadFromFile(spriteSheetPath)||!texture_medicine.loadFromFile(spriteSheetPath)) {
            std::cerr << "Error loading sprite sheet: " << spriteSheetPath << std::endl;
        }
        // Set up the initial sprite
        sprite_shower.setTexture(texture_shower);
        sprite_eating.setTexture(texture_eating);
        sprite_sleeping.setTexture(texture_eating);
        sprite_medicine.setTexture(texture_eating);
        // Apply scaling to the sprite
        sprite_shower.setScale(scaleX, scaleY);
        sprite_eating.setScale(scaleX, scaleY);
        sprite_sleeping.setScale(scaleX, scaleY);
        sprite_medicine.scale(scaleX, scaleY);
        // Update the texture rectangle for the initial frame
        updateSpriteRect_shower();
        updateSpriteRect_eating();
        updateSpriteRect_sleeping();
        updateSpriteRect_medicine();
    }
    baby_ghost(){}

    void startAnimation_sleeping()override{
    isAnimating_sleeping = true;
    currentFrame_sleeping = 0;    // resetting to first frame
    elapsedTime_sleeping = 0.0f;  // resetting elapsed time

    // centerring the sprite's position in the window
    position_sleeping.x = 600.f;
    position_sleeping.y = 350.f;
    sprite_sleeping.setPosition(
        position_sleeping);  // setting the sprite initial position
  }
  // function to update the sleeping animation sprite
  void update_sleeping(float deltaTime) override {
    if (!isAnimating_sleeping) return;  // doesnt udpate if it isnt animating
    elapsedTime_sleeping += deltaTime;

    // showing each frame for a specified duration
    if (elapsedTime_sleeping >= frameDuration_sleeping) {
      currentFrame_sleeping =
          (currentFrame_sleeping + 1) % 3;  // Cycle through all 6 frames
      elapsedTime_sleeping = 0.0f;
    }

    // updating the sprite texture rectangle based on the current frame
    updateSpriteRect_sleeping();
  }
  // function to draw the sleeping function
  void draw_sleeping(sf::RenderWindow& window) override {
    window.draw(sprite_sleeping);
  }
  // function to update the sleeping animation
  void updateSpriteRect_sleeping() override {
    // calculating the frame size based on the sprite sheet
    int frameWidth = texture_sleeping.getSize().x / 2;
    int frameHeight = texture_sleeping.getSize().y / 2;

    // x and y coordinates of the top left corner of the the frame in the
    // spritesheet
    int frameX = 0;
    int frameY = 0;

    // determining which frame to use based on currentFrame
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
    // setting the texture rectangle for the sprite
    sprite_sleeping.setTextureRect(
        sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    // printing the coordinates
    std::cout << "Frame " << currentFrame_sleeping << ": (X: " << frameX
              << ", Y: " << frameY << ")" << std::endl;
  }
  // function to start the animation for eating
  void startAnimation_eating() override {
    isAnimating_eating = true;
    currentFrame_eating = 0;
    elapsedTime_eating = 0.0f;
    position_eating.x = 600.f;
    position_eating.y = 350.f;
    originalPosition_eating = position_eating;
    sprite_eating.setPosition(position_eating);
  }
  // function to update the eating animation
  void update_eating(float deltaTime) override {
    if (!isAnimating_eating) return;

    elapsedTime_eating += deltaTime;

    // showing the first frame for a specified duration, then alternate frames
    if (currentFrame_eating == 0) {
      // staying on the first frame for the duration
      if (elapsedTime_eating >= frameDuration_eating) {
        currentFrame_eating = 1;  // moving to the second frame
        position_eating.x -= 3;
        sprite_eating.setPosition(
            position_eating);  // updating the sprite position
        elapsedTime_eating = 0.0f;
      }
    } else if (currentFrame_eating == 1) {
      // staying on the second frame for a short duration before returning
      if (elapsedTime_eating >= frameDuration_eating / 2) {
        currentFrame_eating = 2;
        elapsedTime_eating = 0.0f;
      }
    } else if (currentFrame_eating == 2) {
      // returning to original position after showing the bottom left frame
      if (elapsedTime_eating >= frameDuration_eating / 2) {
        position_eating = originalPosition_eating;
        sprite_eating.setPosition(position_eating);
        currentFrame_eating = 0;
        elapsedTime_eating = 0.0f;
      }
    }

    // updating the sprite texture based on the current frame
    updateSpriteRect_eating();
  }

  // function to draw he eating animation
  void draw_eating(sf::RenderWindow& window) override {
    window.draw(sprite_eating);
  }
  // function to update the sprite for eating
  void updateSpriteRect_eating() override {
    // calulating the frame size based on the sprite sheet
    int frameWidth = texture_eating.getSize().x / 2;
    int frameHeight = texture_eating.getSize().y / 2;

    int frameX = 0;
    int frameY = 0;

    // determining which frame to use based on currentFrame

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
    // setting the texture rectangle for the sprite
    sprite_eating.setTextureRect(
        sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    // printing out the coordinates for debugging
    std::cout << "Frame " << currentFrame_eating << ": (X: " << frameX
              << ", Y: " << frameY << ")" << std::endl;
  }
  // function to start the animation for showering
  void startAnimation_shower() override {
    isAnimating_shower = true;
    currentFrame_shower = 0;
    elapsedTime_shower = 0.0f;
    position_shower.x = 600.f;
    position_shower.y = 350.f;
    originalPosition_shower = position_shower;
    sprite_shower.setPosition(position_shower);
  }
  // function to update the shower sprite
  void update_shower(float deltaTime) override {
    if (!isAnimating_shower) return;

    elapsedTime_shower += deltaTime;

    // switching frames based on elapsed time
    if (elapsedTime_shower >= frameDuration_shower) {
      currentFrame_shower = (currentFrame_shower + 1) % 4;
      elapsedTime_shower = 0.0f;
    }
    updateSpriteRect_shower();
  }
  // function to draw the shower aniamtion
  void draw_shower(sf::RenderWindow& window) override {
    window.draw(sprite_shower);
  }
  // function to update the shower sprite
  void updateSpriteRect_shower() override {
    // calculating the frame size based on the sprite sheet
    int frameWidth = texture_shower.getSize().x / 2;
    int frameHeight = texture_shower.getSize().y / 2;

    int frameX = (currentFrame_shower % 2) * frameWidth;
    int frameY = (currentFrame_shower / 2) * frameHeight;

    // setting the texture rectangle for the sprite
    sprite_shower.setTextureRect(
        sf::IntRect(frameX, frameY, frameWidth, frameHeight));
    // printing out the coordinates for the frame
    std::cout << "Frame " << currentFrame_shower << ": (X: " << frameX
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

  // function to update the sprite for medicine
  void update_medicine(float deltaTime) override {
    if (!isAnimating_medicine) return;

    elapsedTime_medicine += deltaTime;

    // showing each frame for a specified duration
    if (elapsedTime_medicine >= frameDuration_medicine) {
      currentFrame_medicine =
          (currentFrame_medicine + 1) % 2;  // switching between two frames
      elapsedTime_medicine = 0.0f;
    }

    // udpating the sprite texture  based on the current frame
    updateSpriteRect_medicine();
  }
  // function to drawe the medicine animation
  void draw_medicine(sf::RenderWindow& window) override {
    window.draw(sprite_medicine);
  }
  // function to update the medicine sprite
  void updateSpriteRect_medicine() override {
    // frame dimensions based on the sprite sheet
    int frameWidth = 32;
    int frameHeight = 32;

    // determining which frame to use based on the current frame index
    int frameX = 0;
    int frameY = currentFrame_medicine * frameHeight;

    // setting the texture rectangle for the sprite
    sprite_medicine.setTextureRect(
        sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    // Debugging output to check the frame rect
    std::cout << "Frame rect set: (X: " << frameX << ", Y: " << frameY << ", Width: " << frameWidth << ", Height: " << frameHeight << ")" << std::endl;
}

~baby_ghost(){}

void draw_default_sprite(sf::RenderWindow& window) override{
    window.draw(sprite_shower);
  }
 

};
