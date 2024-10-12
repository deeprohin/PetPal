 #pragma once
#include"MATHGAME.h"
#include <SFML/Graphics.hpp>

class PetStats {
private:
    int health_level;
    int sleep_level;
    int hunger_level;
    int iq_level;
    int total_money;
    sf::Clock stat_timer;
    std::vector<std::string> quotes_ghost;
    std::vector<std::string> quotes_avocado;

public:
    PetStats(); // Constructor

    void updateStats(sf::RenderWindow& window,sf::Font font); // Decreases stats every 30 seconds

    void renderStats(sf::RenderWindow& window, sf::Font& font);  // Draw the stats bars

    void increaseHunger(int amount);
    void increaseSleep(int amount);
    void increaseIQ(int score);
    void increaseMoney(int amount);
    int getMoney() const;

    // Potions for hunger and sleep
    void useHungerPotion();
    void useSleepPotion();

    // Function to determine the color based on the stat level (if needed)
    sf::Color getBarColor(int level);

    //functions to max stats
    void maxHealth();
    void maxSleep();
    void maxHunger();
    void changeMoney(int someMoney);


    void checkStats(sf::RenderWindow& window, sf::Font& font);

};
