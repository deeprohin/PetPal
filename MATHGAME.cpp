#include "MATHGAME.h"

#include <SFML/Audio.hpp>  // Include the Audio module
#include <SFML/Graphics.hpp>

// Constructor initializes the game
math_game::math_game() {
  // Load and play background music
  math_audio.openFromFile("Lobby Music (Original Soundtrack).mp3");
  math_audio.setVolume(100);
  math_audio.play();

  // Load sound effects for correct and incorrect answers
  wrong_audio.openFromFile(
      "Microsoft Windows XP Error - Sound Effect (HD).mp3");
  wrong_audio.setVolume(100);

  // Initialize game state variables
  correct_answers = 0;
  number_of_answers = 0;
  total_time = 50.0;  // Set the total time for solving questions
  std::srand(static_cast<unsigned int>(
      std::time(0)));  // Seed for random number generation
  current_input = "";  // Reset current user input
  game_window = new sf::RenderWindow(sf::VideoMode(1920, 1080),
                                     "Math Game");  // Create game window
  game_window->display();

  display_intro();       // Show the intro screen
  rules_page();          // Show the game rules
  game_window->clear();  // Clear the window for the game
  timer.restart();       // Restart the timer
  run();                 // Start the game loop
}

// Function to generate a new math question
void math_game::generate_question() {
  current_input = "";  // Resetting user input
  // Generate two random numbers and an operator
  int num1 = std::rand() % 100;
  int num2 = std::rand() % 100;
  char operation = "+-*"[std::rand() % 3];  // Randomly select an operation

  // Calculate the correct answer based on the operation
  if (operation == '+') {
    current_answer = num1 + num2;
  } else if (operation == '-') {
    current_answer = num1 - num2;
  } else {
    current_answer = num1 * num2;
  }

  // Create the current question string
  current_question = std::to_string(num1) + " " + operation + " " +
                     std::to_string(num2) + " = ?";
}

// Destructor to clean up resources
math_game::~math_game() {
  math_audio.pause();  // Pause the background music
  delete game_window;  // Delete the game window
}

// Main game loop for running the game
void math_game::run() {
  for (int i = 0; i < 5; i++) {      // Loop to ask 5 questions
    generate_question();             // Generate a new question
    while (game_window->isOpen()) {  // Keep the window open
      bool has_entered = false;      // Track if an answer has been entered
      while (game_window->pollEvent(ev)) {  // Handle events
        // Close the window on close event or Escape key
        if (ev.type == sf::Event::Closed ||
            ev.type == sf::Event::KeyPressed &&
                ev.key.code == sf::Keyboard::Escape) {
          game_window->close();
        }
        // Handle key presses
        if (ev.type == sf::Event::KeyPressed) {
          if (ev.key.code == sf::Keyboard::Enter) {  // Enter key pressed
            // Check if the input is empty
            if (current_input.empty()) {
              break;  // Skip if no input
            }
            // Check if the answer is correct
            if (current_answer == std::stoi(current_input)) {
              correct_answers++;  // Increment correct answers
            }
            number_of_answers++;  // Increment total answers
            has_entered = true;   // Mark that an answer has been entered
            break;                // Exit event handling
          } else if (ev.key.code ==
                     sf::Keyboard::Dash) {  // Handle negative sign
            current_input = '-' + current_input;
          } else if (ev.key.code ==
                     sf::Keyboard::BackSpace) {  // Handle backspace
            if (!current_input.empty()) {
              current_input = current_input.substr(
                  0, current_input.size() - 1);  // Remove last character
            }
          } else if (ev.key.code >= sf::Keyboard::Num0 &&
                     ev.key.code <=
                         sf::Keyboard::Num9) {  // Handle number input
            int number_entered =
                ev.key.code - sf::Keyboard::Num0;  // Get the entered number
            current_input +=
                std::to_string(number_entered);  // Append to current input
          } else {
            // Play wrong answer sound if the key is invalid
            if (wrong_audio.getStatus() != sf::Sound::Playing) {
              wrong_audio.play();
            }
          }
        }
      }
      render();  // Render the current state of the game
      if (has_entered) {
        break;  // Break if an answer was entered
      }
    }
  }
  // Display the final score after 5 questions
  std::cout << "You got " << correct_answers << " out of 5 correct!"
            << std::endl;
  display_results();  // Show the results screen
}

// Function to render the game elements
void math_game::render() {
  game_window->clear(
      sf::Color(230, 230, 220));  // Clear the window with a background color
  sf::Font font;
  if (!font.loadFromFile("dogica.ttf")) {
    std::cout << "Error, font not found" << std::endl;  // Error loading font
  }

  // Display the math question
  sf::Text questionText;
  questionText.setFont(font);
  questionText.setString(current_question);  // Set question text
  questionText.setCharacterSize(55);
  questionText.setFillColor(sf::Color::Black);
  questionText.setPosition(480, 300);
  game_window->draw(questionText);  // Draw the question text

  // Display user input
  sf::Text input_text;
  input_text.setFont(font);
  input_text.setString(current_input);  // Set input text
  input_text.setCharacterSize(40);
  input_text.setFillColor(sf::Color::Black);
  input_text.setPosition(680, 400);
  game_window->draw(input_text);  // Draw user input

  // Display the score
  sf::Text score_text;
  score_text.setFont(font);
  score_text.setFillColor(sf::Color::Black);
  score_text.setString("Score: " +
                       std::to_string(correct_answers));  // Set score text
  score_text.setCharacterSize(40);
  score_text.setPosition(20, 20);
  game_window->draw(score_text);  // Draw score text

  // Display countdown timer
  sf::Text timer_text;
  timer_text.setFont(font);
  double remaining_time =
      51 - timer.getElapsedTime().asSeconds();  // Calculate remaining time
  int remaining_time_int = remaining_time;
  timer_text.setString(std::to_string(remaining_time_int));  // Set timer text
  timer_text.setCharacterSize(40);
  timer_text.setPosition(700, 100);

  // Set color based on remaining time
  if (remaining_time >= 30) {
    timer_text.setFillColor(sf::Color::Black);
  } else if (remaining_time > 10) {
    timer_text.setFillColor(sf::Color(255, 165, 0));  // Orange
  } else {
    timer_text.setFillColor(sf::Color::Red);  // Red for danger
  }
  game_window->draw(timer_text);  // Draw timer text
  game_window->display();         // Update the window

  // Check if time has run out
  if (remaining_time <= 0) {
    display_results();  // Show results if time is up
  }
}

// Function to display the results after the game
void math_game::display_results() {
  game_window->clear(sf::Color(230, 230, 220));  // Clear the window
  sf::Font font;
  if (!font.loadFromFile("Regular.ttf")) {
    std::cout << "Error, font not found" << std::endl;  // Error loading font
  }

  // Display final score
  sf::Text score_text;
  score_text.setFont(font);
  score_text.setFillColor(sf::Color::Black);
  score_text.setString(
      "  GAME OVER!!\n\nPoints Scored: " + std::to_string(correct_answers) +
      "\n\nPress ESC To Exit");
  score_text.setCharacterSize(70);
  score_text.setPosition(550, 300);

  game_window->draw(score_text);  // Draw score text
  game_window->display();         // Update the window

  // Keep the window open until the user decides to close it
  while (game_window->isOpen()) {
    sf::Event event;
    while (game_window->pollEvent(event)) {
      if (event.type == sf::Event::Closed ||
          event.type == sf::Event::KeyPressed &&
              event.key.code == sf::Keyboard::Escape) {
        game_window->close();  // Close the window on close event
      }
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Enter) {
        game_window->close();  // Close the game when Enter is pressed
      }
    }
  }
}

// Function to display the intro screen
void math_game::display_intro() {
  sf::Texture texture_1;
  texture_1.loadFromFile("New Piskel copy (1).png");  // Load intro texture
  sf::Sprite sprite;
  sprite.setTexture(texture_1);  // Set sprite texture
  sprite.setPosition(280, 120);
  sprite.setScale(30.0f, 30.0f);  // Scale the sprite

  Animation intro_scene(&texture_1, sf::Vector2u(6, 1),
                        0.3f);  // Create animation for intro
  float delta_time = 0.0f;
  sf::Clock clock;       // Clock for delta time
  sf::Clock total_time;  // Clock for total time
  while (game_window->isOpen()) {
    sf::Event event;
    while (game_window->pollEvent(event)) {
      if (event.type == sf::Event::Closed ||
          event.type == sf::Event::KeyPressed &&
              ev.key.code == sf::Keyboard::Escape) {
        game_window->close();  // Close the window on close event
      }
    }
    delta_time =
        clock.restart().asSeconds();    // Restart clock and get delta time
    intro_scene.update(0, delta_time);  // Update the animation
    sprite.setTextureRect(
        intro_scene.uv_rect);  // Set the current frame of the animation
    game_window->clear(sf::Color(196, 164, 132));  // Clear the window
    game_window->draw(sprite);                     // Draw the intro sprite
    game_window->display();                        // Update the window
    if (total_time.getElapsedTime().asSeconds() >=
        3) {  // Show intro for 3 seconds
      break;
    }
  }
}

// Function to display the rules page
void math_game::rules_page() {
  sf::Clock clock;  // Clock for timing
  sf::Font font;
  if (!font.loadFromFile("Regular.ttf")) {
    std::cout << "Error, font not found" << std::endl;  // Error loading font
  }
  while (game_window->isOpen()) {
    sf::Event event;
    bool escape = false;                     // Flag for exit condition
    while (game_window->pollEvent(event)) {  // Handle events
      if (event.type == sf::Event::Closed ||
          event.type == sf::Event::KeyPressed &&
              event.key.code == sf::Keyboard::Escape) {
        game_window->close();  // Close the window on close event
      }
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Enter) {
        escape = true;  // Set exit flag if Enter is pressed
      }
    }
    game_window->clear(sf::Color(230, 230, 220));  // Clear the window
    if (escape) {
      break;  // Exit if Enter was pressed
    }

    // Display instructions
    sf::Text welcome1;
    welcome1.setFont(font);
    welcome1.setFillColor(sf::Color::Black);
    welcome1.setString(
        "Welcome to PetPal Math Game!\n\n\nInstructions:\n\n1) You have 50 "
        "seconds to answer 5 math questions\n\n2) Type solution and hit enter "
        "to answer\n\n3) Type - for negative\n\n4) Use delete key to remove "
        "entered number\n\n5) Press Enter to Start Game\n\n\nGood Luck!");
    welcome1.setCharacterSize(35);
    welcome1.setPosition(30, 30);
    game_window->draw(welcome1);  // Draw instructions
    game_window->display();       // Update the window
  }
}

// Function to get the score of the player
int math_game::getScore() {
  return correct_answers;  // Return the number of correct answers
}
