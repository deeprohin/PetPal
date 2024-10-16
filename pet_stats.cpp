#include "pet_stats.h"

#include <algorithm>  // for std::max and std::min
#include <iostream>

PetStats::PetStats()
    : health_level(25),  // Set initial health level to 25
      sleep_level(25),   // Set initial sleep level to 25
      hunger_level(25),  // Set initial hunger level to 25
      iq_level(50),      // Set initial IQ level to 50
      total_money(1000) {
  stat_timer.restart();
}
void PetStats::updateStats(sf::RenderWindow& window, sf::Font font) {
  // Update stats every 30 seconds
  if (stat_timer.getElapsedTime().asSeconds() >= 30) {
    // Update health level, but not if it's already 0
    if (health_level > 0) {
      health_level = std::max(0, health_level - 10);
    }

    // Update sleep level, but not if it's already 0
    if (sleep_level > 0) {
      sleep_level = std::max(0, sleep_level - 10);
    }

    // Update hunger level, but not if it's already 0
    if (hunger_level > 0) {
      hunger_level = std::max(0, hunger_level - 10);
    }

    // Update IQ level, but not if it's already 0
    if (iq_level > 0) {
      iq_level = std::max(0, iq_level - 5);
    }

    stat_timer.restart();
  }
}

void PetStats::renderStats(sf::RenderWindow& window, sf::Font& font) {
  // Health bar
  sf::RectangleShape health_bar(sf::Vector2f(250 * health_level / 100, 30));
  health_bar.setFillColor(sf::Color::Black);
  health_bar.setPosition(20, 50);
  window.draw(health_bar);

  sf::Text health_text;
  health_text.setFont(font);
  health_text.setCharacterSize(44);
  health_text.setFillColor(sf::Color::Black);
  health_text.setPosition(50, 2);
  health_text.setString("Health Bar: ");
  window.draw(health_text);

  // Sleep bar
  sf::RectangleShape sleep_bar(sf::Vector2f(250 * sleep_level / 100, 30));
  sleep_bar.setFillColor(sf::Color::Black);
  sleep_bar.setPosition(350, 50);
  window.draw(sleep_bar);

  sf::Text sleep_bar_text;
  sleep_bar_text.setFont(font);
  sleep_bar_text.setCharacterSize(44);
  sleep_bar_text.setFillColor(sf::Color::Black);
  sleep_bar_text.setPosition(350, 2);
  sleep_bar_text.setString("Sleep Bar: ");
  window.draw(sleep_bar_text);

  // Hunger bar
  sf::RectangleShape hunger_bar(sf::Vector2f(250 * hunger_level / 100, 30));
  hunger_bar.setFillColor(sf::Color::Black);
  hunger_bar.setPosition(970, 50);
  window.draw(hunger_bar);

  sf::Text hunger_text;
  hunger_text.setFont(font);
  hunger_text.setCharacterSize(44);
  hunger_text.setFillColor(sf::Color::Black);
  hunger_text.setPosition(970, 2);
  hunger_text.setString("Hunger Bar: ");
  window.draw(hunger_text);

  // IQ bar
  sf::RectangleShape iq_bar(sf::Vector2f(250 * iq_level / 100.0f, 30));
  iq_bar.setFillColor(sf::Color::Black);
  iq_bar.setPosition(650, 50);
  window.draw(iq_bar);

  sf::Text iq_bar_text;
  iq_bar_text.setFont(font);
  iq_bar_text.setCharacterSize(44);
  iq_bar_text.setFillColor(sf::Color::Black);
  iq_bar_text.setPosition(650, 2);
  iq_bar_text.setString("IQ Bar: ");
  window.draw(iq_bar_text);

  // Money text
  sf::Text money_text;
  money_text.setFont(font);
  money_text.setCharacterSize(44);
  money_text.setFillColor(sf::Color::Black);
  money_text.setPosition(1320, 20);
  money_text.setString(std::to_string(total_money));
  window.draw(money_text);

  // Coin sign
  sf::Texture coin_sign_texture;
  if (!coin_sign_texture.loadFromFile("coin.png")) {
    std::cout << "Image Not Found" << std::endl;
  }
  sf::Sprite coin_sign;
  coin_sign.setTexture(coin_sign_texture);
  coin_sign.setPosition(1240, 20);
  coin_sign.setScale(0.1f, 0.1f);
  window.draw(coin_sign);  // Draw the coin sign
}

// Function to determine color based on the stat level (if needed)
sf::Color PetStats::getBarColor(int level) {
  return sf::Color::Black;  // Return black color for now
}

void PetStats::increaseHunger(int amount) {
  hunger_level = std::min(100, hunger_level + amount);
}

void PetStats::increaseSleep(int amount) {
  sleep_level = std::min(100, sleep_level + amount);
}

void PetStats::increaseIQ(int score) {
  if (score >= 0 && score <= 5) {
    iq_level = std::min(100, iq_level + (score * 5));
    std::cout << iq_level << std::endl;
  }
}

void PetStats::increaseMoney(int amount) { total_money += amount; }

int PetStats::getMoney() const { return total_money; }

void PetStats::useHungerPotion() { hunger_level = 100; }

void PetStats::useSleepPotion() { sleep_level = 100; }
void PetStats::maxHealth() { health_level = 100; }

void PetStats::maxSleep() { sleep_level = 100; }

void PetStats::maxHunger() { hunger_level = 100; }

void PetStats::changeMoney(int someMoney) {
  total_money = total_money + someMoney;
}
void PetStats::checkStats(sf::RenderWindow& window, sf::Font& font) {
  // Variable to keep track of where to position the next warning
  float warning_position_y = 400;  // Start at Y position 400
  float warning_position_x = 20;   // Fixed X position at 20

  // Display warnings if any stat is at 0
  if (health_level <= 0) {
    sf::Text warning_text;
    warning_text.setFont(font);
    warning_text.setCharacterSize(44);
    warning_text.setFillColor(sf::Color::Red);
    warning_text.setPosition(warning_position_x,
                             warning_position_y);  // X = 20, Y starts at 400
    warning_text.setString("WARNING!! HEALTH IS 0");
    window.draw(warning_text);
    warning_position_y += 60;  // Move down for the next warning
  }

  if (sleep_level <= 0) {
    sf::Text warning_text;
    warning_text.setFont(font);
    warning_text.setCharacterSize(44);
    warning_text.setFillColor(sf::Color::Red);
    warning_text.setPosition(warning_position_x, warning_position_y);  // X = 20
    warning_text.setString("WARNING!! SLEEP IS 0");
    window.draw(warning_text);
    warning_position_y += 60;
  }

  if (hunger_level <= 0) {
    sf::Text warning_text;
    warning_text.setFont(font);
    warning_text.setCharacterSize(44);
    warning_text.setFillColor(sf::Color::Red);
    warning_text.setPosition(warning_position_x, warning_position_y);  // X = 20
    warning_text.setString("WARNING!! HUNGER IS 0");
    window.draw(warning_text);
    warning_position_y += 60;
  }

  if (iq_level <= 0) {
    sf::Text warning_text;
    warning_text.setFont(font);
    warning_text.setCharacterSize(44);
    warning_text.setFillColor(sf::Color::Red);
    warning_text.setPosition(warning_position_x, warning_position_y);  // X = 20
    warning_text.setString("WARNING!! IQ IS 0");
    window.draw(warning_text);
    warning_position_y += 60;
  }
}
