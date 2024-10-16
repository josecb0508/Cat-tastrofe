#include "Enemy.hpp"

Enemy::Enemy(const std::string& spriteSheet, const sf::Vector2f& position, float health)
    : health_(health), size_(24, 28) 
{
    texture_.loadFromFile(spriteSheet);
    sprite_.setTexture(texture_);
    sprite_.setPosition(position);
    sprite_.setScale(5, 5);  
    bounding_square_.setSize(sf::Vector2f(size_.x * sprite_.getScale().x, size_.y * sprite_.getScale().y));
    bounding_square_.setFillColor(sf::Color::Transparent);
    bounding_square_.setOutlineColor(sf::Color::Transparent);      
    bounding_square_.setOutlineThickness(1);             
    bounding_square_.setPosition(position);
}

void Enemy::Draw(sf::RenderWindow& window) {
    window.draw(sprite_);      
    window.draw(bounding_square_); 
}
sf::FloatRect Enemy::GetHitbox() const {
    return bounding_square_.getGlobalBounds();
}
void Enemy::TakeDamage(float damage) {
    health_ -= damage;
    if (health_ < 0) {
        health_ = 0; 
    }
}

bool Enemy::IsDead() const {
    return health_ <= 0;
}