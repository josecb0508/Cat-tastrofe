#include "Enemy.hpp"

Enemy::Enemy(const std::string& spriteSheet, const sf::Vector2f& position, float health, 
             const sf::Vector2i& size, const sf::Vector2f& scale, const sf::Color& hitbox_color, float strength, int beta_particles)
    : health_(health), strength_(strength), size_(size), beta_particles_(beta_particles)
{
    texture_.loadFromFile(spriteSheet);
    sprite_.setTexture(texture_);
    sprite_.setPosition(position);
    sprite_.setScale(scale);  
    bounding_square_.setSize(sf::Vector2f(size_.x * scale.x, size_.y * scale.y));
    bounding_square_.setFillColor(sf::Color::Transparent);
    bounding_square_.setOutlineColor(hitbox_color);      
    bounding_square_.setOutlineThickness(1);             
    bounding_square_.setPosition(position);
}

void Enemy::setPosition(const sf::Vector2f& position)
{
    sprite_.setPosition(position);
    bounding_square_.setPosition(position);
}

void Enemy::setHealth(float health)
{
    health_ = health; 
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