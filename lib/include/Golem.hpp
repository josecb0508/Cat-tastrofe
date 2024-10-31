#ifndef GOLEM_HPP
#define GOLEM_HPP

#include "Enemy.hpp"

class Golem : public Enemy {
public:
    Golem(const std::string& spriteSheet, const std::string& attackSpriteSheet, const sf::Vector2f& Position);
    void Move(float deltaTime, const sf::Vector2f& targetPosition);
    void UpdateDirection(const sf::Vector2f& targetPosition);
        
private:
    sf::Texture attack_texture_;
    sf::Sprite attack_sprite_;
    float current_direction_;
};

#endif