#include "Animation.h"

// Constructor for the Animation class
Animation::Animation(sf::Texture* texture, sf::Vector2u image_count,
                     float switch_time) {
  // storing the number of frames in the animation and the time between frame
  // switches
  this->image_count = image_count;
  this->switch_time = switch_time;

  // initialising the total time  Initialize the total time passed for frame
  // switching and set the current frame on the X-axis
  total_time = 0.0f;
  current_image.x = 0;

  // calculating the width and height of a single frame from the texture size
  uv_rect.width = texture->getSize().x / float(image_count.x);
  uv_rect.height = texture->getSize().y / float(image_count.y);
}

// update function to update hte animation
void Animation::update(int row, float delta_time) {
  // setting the current image row corresponding to a specific animation
  current_image.y = row;

  // incrementting the total time with the time elapsed since the last frame
  total_time += delta_time;

  // checking if enough time has passed to switch to the next frame
  if (total_time >= switch_time) {
    // reducing total time by the switch time to prevent skipping frames
    total_time -= switch_time;

    // moving to the next frame on the x axis
    current_image.x++;

    // looping the animation back to the first frame if the current frame
    // exceeds the image count
    if (current_image.x >= image_count.x) {
      current_image.x = 0;
    }
  }

  // Updating the texture to display the current frame
  uv_rect.left = current_image.x * uv_rect.width;
  uv_rect.top = current_image.y * uv_rect.height;
}
Animation::~Animation() {}