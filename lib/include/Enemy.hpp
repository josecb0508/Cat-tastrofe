#ifndef ENEMY_HPP  
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Enemy {
public:
    Enemy(const std::string& spriteSheet, const sf::Vector2f& position, float health);
    void Draw(sf::RenderWindow& window);
    void TakeDamage(float damage);
    bool IsDead() const;
    sf::FloatRect GetHitbox() const;

private:
    sf::Texture texture_;
    sf::Sprite sprite_;
    float health_;
    sf::RectangleShape bounding_square_;
    sf::Vector2i size_;
};

#endif 
