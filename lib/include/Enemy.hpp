#ifndef ENEMY_HPP  
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Enemy {
public:
     Enemy(const std::string& spriteSheet, const sf::Vector2f& position, float health,  const sf::Vector2i& size, const sf::Vector2f& scale, const sf::Color& hitbox_color, float strength, int beta_particles);
     void setPosition(const sf::Vector2f& position);
     void setHealth(float health);
     void Draw(sf::RenderWindow& window);
     void TakeDamage(float damage);
     bool IsDead() const;
     sf::FloatRect GetHitbox() const;
     virtual float GetStrength() const { return strength_; }
     void DropParticles();

protected:
    sf::Texture texture_;
    sf::Sprite sprite_;
    float health_;
    float strength_;
    sf::RectangleShape bounding_square_;
    sf::Vector2i size_;
    int beta_particles_; //experience dropped by enemies
};


#endif 
