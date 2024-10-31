#include "Golem.hpp"
#include <cmath>

Golem::Golem(const std::string& spriteSheet, const std::string& attackSpriteSheet, const sf::Vector2f& position)
    : Enemy(spriteSheet, position, 50, {20, 25}, {3, 3}, sf::Color::Transparent)
{
    attackTexture_.loadFromFile(attackSpriteSheet);
    attackSprite_.setTexture(attackTexture_);
    attackSprite_.setPosition(position);
}
void Golem::Move(float deltaTime, const sf::Vector2f& targetPosition) {
    sf::Vector2f direction = targetPosition - sprite_.getPosition();
    float distance = std::sqrt(std::pow(direction.x, 2) + std::pow(direction.y, 2));

    if (distance > 0) {
        direction /= distance; 
        float speed = 100.0f;
        sprite_.move(direction * speed * deltaTime);
        UpdateDirection(targetPosition);
    }
}

void Golem::UpdateDirection(const sf::Vector2f& targetPosition) {
    float dx = targetPosition.x - sprite_.getPosition().x;
    float dy = targetPosition.y - sprite_.getPosition().y;
    if (std::abs(dx) > std::abs(dy)) {
        currentDirection_ = (dx > 0) ? 3 : 2; 
    } else {

        currentDirection_ = (dy > 0) ? 1 : 0; 
    }
}