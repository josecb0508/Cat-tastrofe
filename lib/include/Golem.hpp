#ifndef GOLEM_HPP
#define GOLEM_HPP

#include "Enemy.hpp"

class Golem : public Enemy {
public:
    Golem(const std::string& spriteSheet, const std::string& attackSpriteSheet, const sf::Vector2f& Position);
    void Move(float deltaTime, const sf::Vector2f& targetPosition);
    void UpdateDirection(const sf::Vector2f& targetPosition);
        
private:
    sf::Texture attackTexture_;
    sf::Sprite attackSprite_;
    float currentDirection_;
};

#endif