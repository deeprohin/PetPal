#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class SpriteLoader {
public:
    static sf::Texture sleeping_button_texture;
    static sf::Sprite sleeping_button_sprite;

    static sf::Texture adult_avo_normal;
    static sf::Sprite adult_avo_normal_sprite;

    static sf::Texture baby_avo_normal;
    static sf::Sprite baby_avo_normal_sprite;

    static sf::Texture adult_ghost_normal;
    static sf::Sprite adult_ghost_normal_sprite;

    static sf::Texture baby_ghost_normal;
    static sf::Sprite baby_ghost_normal_sprite;

    static sf::Texture shower_button_texture;
    static sf::Sprite shower_button_sprite;

    static sf::Texture game_button_texture;
    static sf::Sprite game_button_sprite;

    static sf::Texture food_button_texture;
    static sf::Sprite food_button_sprite;

    static sf::Texture health_button_texture;
    static sf::Sprite health_button_sprite;

    static sf::Texture shopping_button_texture;
    static sf::Sprite shopping_button_sprite;

    static sf::Texture info_button_texture;
    static sf::Sprite info_button_sprite;

    static sf::Texture math_button_texture;
    static sf::Sprite math_button_sprite;

    static bool loadResources() {
        // Load sleeping button texture
        if (!sleeping_button_texture.loadFromFile("moon.png")) {
            std::cout << "Sleeping button image not found." << std::endl;
            return false;
        }
        sleeping_button_sprite.setTexture(sleeping_button_texture);
        sleeping_button_sprite.setPosition(40, 130);

        // Load adult avo texture
        if (!adult_avo_normal.loadFromFile("bigCharNormalAvo.png")) return false;
        adult_avo_normal_sprite.setTexture(adult_avo_normal);
        adult_avo_normal_sprite.setPosition(600, 350);
        adult_avo_normal_sprite.setScale(8.0f, 8.0f);

        // Load baby avo texture
        if (!baby_avo_normal.loadFromFile("smallAvoNormal.png")) return false;
        baby_avo_normal_sprite.setTexture(baby_avo_normal);
        baby_avo_normal_sprite.setPosition(600, 350);
        baby_avo_normal_sprite.setScale(8.0f, 8.0f);

        // Load adult ghost texture
        if (!adult_ghost_normal.loadFromFile("bigCharNormalGhost.png")) return false;
        adult_ghost_normal_sprite.setTexture(adult_ghost_normal);
        adult_ghost_normal_sprite.setPosition(600, 350);
        adult_ghost_normal_sprite.setScale(8.0f, 8.0f);

        // Load baby ghost texture
        if (!baby_ghost_normal.loadFromFile("smallGhostNormal.png")) return false;
        baby_ghost_normal_sprite.setTexture(baby_ghost_normal);
        baby_ghost_normal_sprite.setPosition(600, 350);
        baby_ghost_normal_sprite.setScale(8.0f, 8.0f);

        // Load shower button texture
        if (!shower_button_texture.loadFromFile("shower (1).png")) {
            std::cout << "Shower button image not found." << std::endl;
            return false;
        }
        shower_button_sprite.setTexture(shower_button_texture);
        shower_button_sprite.setPosition(470, 130);

        // Load game button texture
        if (!game_button_texture.loadFromFile("console.png")) {
            std::cout << "Game button image not found." << std::endl;
            return false;
        }
        game_button_sprite.setTexture(game_button_texture);
        game_button_sprite.setPosition(900, 130);

        // Load food button texture
        if (!food_button_texture.loadFromFile("cutlery.png")) {
            std::cout << "Food button image not found." << std::endl;
            return false;
        }
        food_button_sprite.setTexture(food_button_texture);
        food_button_sprite.setPosition(1310, 130);

        // Load health button texture
        if (!health_button_texture.loadFromFile("first-aid-kit.png")) {
            std::cout << "Health button image not found." << std::endl;
            return false;
        }
        health_button_sprite.setTexture(health_button_texture);
        health_button_sprite.setPosition(40, 680);

        // Load shopping button texture
        if (!shopping_button_texture.loadFromFile("grocery-cart.png")) {
            std::cout << "Shopping button image not found." << std::endl;
            return false;
        }
        shopping_button_sprite.setTexture(shopping_button_texture);
        shopping_button_sprite.setPosition(470, 680);

        // Load info button texture
        if (!info_button_texture.loadFromFile("info.png")) {
            std::cout << "Info button image not found." << std::endl;
        }
        info_button_sprite.setTexture(info_button_texture);
        info_button_sprite.setPosition(1310, 680);

        // Load math button texture
        if (!math_button_texture.loadFromFile("math.png")) {
            std::cout << "Math button image not found." << std::endl;
        }
        math_button_sprite.setTexture(math_button_texture);
        math_button_sprite.setPosition(900, 680);

        return true;
    }
};

// Definition of static members
sf::Texture SpriteLoader::sleeping_button_texture;
sf::Sprite SpriteLoader::sleeping_button_sprite;

sf::Texture SpriteLoader::adult_avo_normal;
sf::Sprite SpriteLoader::adult_avo_normal_sprite;

sf::Texture SpriteLoader::baby_avo_normal;
sf::Sprite SpriteLoader::baby_avo_normal_sprite;

sf::Texture SpriteLoader::adult_ghost_normal;
sf::Sprite SpriteLoader::adult_ghost_normal_sprite;

sf::Texture SpriteLoader::baby_ghost_normal;
sf::Sprite SpriteLoader::baby_ghost_normal_sprite;

sf::Texture SpriteLoader::shower_button_texture;
sf::Sprite SpriteLoader::shower_button_sprite;

sf::Texture SpriteLoader::game_button_texture;
sf::Sprite SpriteLoader::game_button_sprite;

sf::Texture SpriteLoader::food_button_texture;
sf::Sprite SpriteLoader::food_button_sprite;

sf::Texture SpriteLoader::health_button_texture;
sf::Sprite SpriteLoader::health_button_sprite;

sf::Texture SpriteLoader::shopping_button_texture;
sf::Sprite SpriteLoader::shopping_button_sprite;

sf::Texture SpriteLoader::info_button_texture;
sf::Sprite SpriteLoader::info_button_sprite;

sf::Texture SpriteLoader::math_button_texture;
sf::Sprite SpriteLoader::math_button_sprite;
