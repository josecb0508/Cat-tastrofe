#ifndef CAT_HPP
#define CAT_HPP

#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "Enemy.hpp"

class Cat {
public:
    Cat(const std::string& spriteSheet, const sf::Vector2f& initialPosition);
    void Move(float deltaTime, const Map& room, Enemy& enemy);
    void Draw(sf::RenderWindow& window);
    void SetPosition(const sf::Vector2f& position);
    sf::Vector2f GetPosition() const;
    void GetDamage(float delta_time, Enemy& enemy);

private:
    void UpdateHealthBar();
    void AnimateMovement(float delta_time);     
    void AnimateAttack(float delta_time);           
    void SetDirection(int row);               
    void StartAttack();                         
    void ResetFrame();
    void Scratch(float delta_time, Enemy& enemy);
    sf::Texture texture_;                      
    sf::Sprite sprite_;                         
    sf::IntRect current_frame_;                
    int frame_width_;                          
    int frame_height_;                      
    int frame_count_;                     
    sf::Vector2f velocity_;                    
    sf::Vector2f last_valid_position_;          
    int current_row_;      
    int direction_before_attack_;  
    bool moving_;                          
    float animation_time_;                      
    float frame_duration_;                       
    bool attacking_;                             
    float attack_duration_;                      
    float attack_timer_;                        
    sf::RectangleShape square_;         
    sf::RectangleShape hp_bar;        
    sf::RectangleShape bounding_square_;       
    sf::Vector2i size_;                       
    static bool IsRectContained(const sf::FloatRect& bounds, const sf::FloatRect& rect); 
    sf::RectangleShape hp_bar_background_;
    float max_hp_;
    float current_hp_;  
    float strength_cat_;
    float defense_Cat_;  
};

#endif