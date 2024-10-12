#ifndef BABY_GHOST_H
#define BABY_GHOST_H
#include "Shower.h"
#include "Eating.h"
#include "Sleeping.h"
#include "Medicine.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "pet_stats.h"
class baby_ghost : public Shower,public Eating,public Sleeping,public Medicine,public PetStats{
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

    void startAnimation_sleeping()override{
    isAnimating_sleeping = true;
    currentFrame_sleeping = 0; // Reset to first frame
    elapsedTime_sleeping = 0.0f; // Reset elapsed time

    // Center the sprite's position in the window
    position_sleeping.x = 600.f; // Center X position
    position_sleeping.y = 350.f; // Center Y position
    sprite_sleeping.setPosition(position_sleeping); // Set the sprite's initial position
}

void update_sleeping(float deltaTime) override{
    if (!isAnimating_sleeping) return; // Do not update if not animating

    // Accumulate time
    elapsedTime_sleeping += deltaTime;

    // Show each frame for a specified duration
    if (elapsedTime_sleeping >= frameDuration_sleeping) {
        currentFrame_sleeping = (currentFrame_sleeping + 1) % 3; // Cycle through all 6 frames
        elapsedTime_sleeping = 0.0f; // Reset elapsed time
    }

    // Update the sprite's texture rectangle based on the current frame
    updateSpriteRect_sleeping();
}

void draw_sleeping(sf::RenderWindow& window) override{
    window.draw(sprite_sleeping);
}

void updateSpriteRect_sleeping() override{
    // Calculate the frame size based on the sprite sheet
    int frameWidth = texture_sleeping.getSize().x / 2;  // There are 4 columns
    int frameHeight = texture_sleeping.getSize().y/2; // There is 1 row

    // x and y coordinates of the top-left corner of the fcrame in the sprite sheet
    int frameX = 0;
    int frameY = 0;

    // Determine which frame to use based on currentFrame
        switch (currentFrame_sleeping)
    {
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
        // You can add more frames here as needed
    }
    // Set the texture rectangle for the sprite
    sprite_sleeping.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    // Optional: Print out the frame's coordinates for debugging
    std::cout << "Frame " << currentFrame_sleeping << ": (X: " << frameX << ", Y: " << frameY << ")" << std::endl;
}

void startAnimation_eating() override{
    isAnimating_eating = true;
    currentFrame_eating = 0; // Reset to first frame
    elapsedTime_eating = 0.0f; // Reset elapsed time
    position_eating.x = 600.f; // Start position (center of the window)
    position_eating.y = 350.f; // Y position
    originalPosition_eating = position_eating; // Store the original position
    sprite_eating.setPosition(position_eating); // Set the sprite's initial position
}

void update_eating(float deltaTime) override{
    if (!isAnimating_eating) return; // Do not update if not animating

    // Accumulate time
    elapsedTime_eating += deltaTime;

    // Show the first frame for a specified duration, then alternate frames
    if (currentFrame_eating == 0) {
        // Stay on the first frame for the duration
        if (elapsedTime_eating >= frameDuration_eating) {
            currentFrame_eating = 1; // Move to the second frame (top right)
            position_eating.x -= 3;  // Move left 3 units
            sprite_eating.setPosition(position_eating); // Update the sprite's position
            elapsedTime_eating = 0.0f; // Reset elapsed time
        }
    } else if (currentFrame_eating == 1) {
        // Stay on the second frame for a short duration before returning
        if (elapsedTime_eating >= frameDuration_eating / 2) {
            currentFrame_eating = 2; // Move to the third frame (bottom left)
            elapsedTime_eating = 0.0f; // Reset elapsed time
        }
    } else if (currentFrame_eating == 2) {
        // Return to original position after showing the bottom left frame
        if (elapsedTime_eating >= frameDuration_eating / 2) {
            position_eating = originalPosition_eating; // Return to original position
            sprite_eating.setPosition(position_eating); // Update the sprite's position
            currentFrame_eating = 0; // Reset back to first frame
            elapsedTime_eating = 0.0f; // Reset elapsed time
        }
    }

    // Update the sprite's texture rectangle based on the current frame
    updateSpriteRect_eating();
}


void draw_eating(sf::RenderWindow& window) override{
    window.draw(sprite_eating);
}

void updateSpriteRect_eating() override{
     // Calculate the frame size based on the sprite sheet
    int frameWidth = texture_eating.getSize().x / 2;  // There are 3 columns in the sprite sheet
    int frameHeight = texture_eating.getSize().y/2; // The height is the same for all frames

    // x and y coordinates of the top-left corner of the frame in the sprite sheet
    int frameX = 0;
    int frameY = 0;

    // Determine which frame to use based on currentFrame
    
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
    // Set the texture rectangle for the sprite
    sprite_eating.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    // Optional: Print out the frame's coordinates for debugging
    std::cout << "Frame " << currentFrame_eating << ": (X: " << frameX << ", Y: " << frameY << ")" << std::endl;
}

 void startAnimation_shower() override {
        isAnimating_shower = true;
        currentFrame_shower = 0; // Reset to the first frame
        elapsedTime_shower = 0.0f; // Reset elapsed time
        position_shower.x = 600.f; // Start position (center of the window)
        position_shower.y = 350.f; // Y position
        originalPosition_shower = position_shower; // Store the original position
        sprite_shower.setPosition(position_shower); // Set the sprite's initial position
    }

    void update_shower(float deltaTime) override {
        if (!isAnimating_shower) return; // Do not update if not animating

        // Accumulate time
        elapsedTime_shower += deltaTime;

        // Switch frames based on elapsed time
        if (elapsedTime_shower >= frameDuration_shower) {
            currentFrame_shower = (currentFrame_shower + 1) % 4; // Loop back to the first frame after the last one
            elapsedTime_shower = 0.0f; // Reset elapsed time
        }
        updateSpriteRect_shower();
    }

    void draw_shower(sf::RenderWindow& window)override{
    window.draw(sprite_shower);
}

void updateSpriteRect_shower() override{
    // Calculate the frame size based on the sprite sheet
    int frameWidth = texture_shower.getSize().x / 2;  // There are 5 columns in the first row
    int frameHeight = texture_shower.getSize().y/2; // Only 1 row in the sprite sheet

    // x and y coordinates of the top-left corner of the frame in the sprite sheet
    int frameX = (currentFrame_shower % 2) * frameWidth;
    int frameY = (currentFrame_shower / 2) * frameHeight;


    // Set the texture rectangle for the sprite
    sprite_shower.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));
    // Optional: Print out the frame's coordinates for debugging
    std::cout << "Frame " << currentFrame_shower << ": (X: " << frameX << ", Y: " << frameY << ")" << std::endl;
}

void startAnimation_medicine() override{
    isAnimating_medicine = true;
    currentFrame_medicine = 0; // Reset to first frame
    elapsedTime_medicine = 0.0f; // Reset elapsed time
    position_medicine.x = 600.f; // Start position (center of the window)
    position_medicine.y = 350.f; // Y position
    originalPosition_medicine = position_medicine; // Store the original position
    sprite_medicine.setPosition(position_medicine); // Set the sprite's initial position
}


void update_medicine(float deltaTime) override{
    if (!isAnimating_medicine) return; // Do not update if not animating

    // Accumulate time
    elapsedTime_medicine += deltaTime;

    // Show each frame for a specified duration
    if (elapsedTime_medicine >= frameDuration_medicine) {
        currentFrame_medicine = (currentFrame_medicine + 1) % 2; // Switch between 0 and 1 (two frames)
        elapsedTime_medicine = 0.0f; // Reset elapsed time
    }

    // Update the sprite's texture rectangle based on the current frame
    updateSpriteRect_medicine();
}

void draw_medicine(sf::RenderWindow& window) override{
    window.draw(sprite_medicine);
}

void updateSpriteRect_medicine() override{
       // Frame dimensions based on the sprite sheet
    int frameWidth = 32;  // Width of one frame
    int frameHeight = 32; // Height of one frame

     // Determine which frame to use based on the current frame index
    int frameX = 0;
    int frameY = currentFrame_medicine * frameHeight;  // Determine Y position based on current frame


    // Set the texture rectangle for the sprite
    sprite_medicine.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));

    // Debugging output to check the frame rect
    std::cout << "Frame rect set: (X: " << frameX << ", Y: " << frameY << ", Width: " << frameWidth << ", Height: " << frameHeight << ")" << std::endl;
}

~baby_ghost(){}




};
#endif