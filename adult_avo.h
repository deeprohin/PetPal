#ifndef ADULT_AVO_H
#define ADULT_AVO_H

#include "Shower.h"
#include "Eating.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class adult_avo : public Shower{
public:
    // Constructor to load the sprite sheet for an activity with scaling for showering
    adult_avo(const std::string& spriteSheetPath, float frameDuration, float scaleX = 1.0f, float scaleY = 1.0f)
        :Shower(spriteSheetPath, frameDuration, scaleX, scaleY){//,Eating(spriteSheetPath, frameDuration, scaleX, scaleY){ 
        if (!texture_shower.loadFromFile(spriteSheetPath)) {
            std::cerr << "Error loading sprite sheet: " << spriteSheetPath << std::endl;
        }
        // Set up the initial sprite
        sprite_shower.setTexture(texture_shower);
        // Apply scaling to the sprite
        sprite_shower.setScale(scaleX, scaleY);
        // Update the texture rectangle for the initial frame
        updateSpriteRect_shower();
    }

    // Start the animation
    void startAnimation_shower() override {
        isAnimating_shower = true;
        currentFrame_shower = 0; // Reset to the first frame
        elapsedTime_shower = 0.0f; // Reset elapsed time
        position_shower.x = 600.f; // Start position (center of the window)
        position_shower.y = 350.f; // Y position
        originalPosition_shower = position_shower; // Store the original position
        sprite_shower.setPosition(position_shower); // Set the sprite's initial position
    }
    // Update the animation based on the time elapsed
    void update_shower(float deltaTime) override {
        if (!isAnimating_shower) return; // Do not update if not animating

        // Accumulate time
        elapsedTime_shower += deltaTime;

        // Switch frames based on elapsed time
        if (elapsedTime_shower >= frameDuration_shower) {
            currentFrame_shower = (currentFrame_shower + 1) % 5; // Loop back to the first frame after the last one
            elapsedTime_shower = 0.0f; // Reset elapsed time
        }
        updateSpriteRect_shower();
    }
    void draw_shower(sf::RenderWindow& window)override{
    window.draw(sprite_shower);
}
// Update the sprite rectangle based on the current frame
void updateSpriteRect_shower() override{
    // Calculate the frame size based on the sprite sheet
    int frameWidth = texture_shower.getSize().x / 5;  // There are 5 columns in the first row
    int frameHeight = texture_shower.getSize().y; // Only 1 row in the sprite sheet

    // x and y coordinates of the top-left corner of the frame in the sprite sheet
    int frameX = 0;
    int frameY = 0;

    // Determine which frame to use based on currentFrame
    switch (currentFrame_shower) {
        case 0: frameX = 0; break;
        case 1: frameX = frameWidth; break;
        case 2: frameX = 2 * frameWidth; break;
        case 3: frameX = 3 * frameWidth; break;
        case 4: frameX = 4 * frameWidth; break;
    }
    // Set the texture rectangle for the sprite
    sprite_shower.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));
    // Optional: Print out the frame's coordinates for debugging
    std::cout << "Frame " << currentFrame_shower << ": (X: " << frameX << ", Y: " << frameY << ")" << std::endl;
}
#endif // ADULT_AVO_H
};