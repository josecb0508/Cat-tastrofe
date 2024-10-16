#ifndef CAT_HPP
#define CAT_HPP

#include <SFML/Graphics.hpp>
#include "Map.hpp"

class Cat {
public:
    Cat(const std::string& spriteSheet, const sf::Vector2f& initialPosition);
    void move(float deltaTime, const Map& room);
    void draw(sf::RenderWindow& window);
    static bool isRectContained(const sf::FloatRect& outerRect, const sf::FloatRect& innerRect);

private:
    void Animation(float deltaTime);
    void Direction(int row);
    void attack();
    void Attack_Cat(float deltaTime);

    sf::Texture texture_;
    sf::Sprite sprite_;
    sf::Vector2f velocity_;
    sf::IntRect current_frame_;
    float animation_time_;
    float frame_duration_;
    int current_row_;
    int frame_count_;
    int frame_width_;
    int frame_height_;
    bool moving_;
    sf::RectangleShape square_;
    sf::RectangleShape bounding_square_;
    sf::Vector2i size_;
    bool attacking_;
    float attack_duration_;
    float attack_timer_;

    sf::Vector2f last_valid_position_;
};

#endif