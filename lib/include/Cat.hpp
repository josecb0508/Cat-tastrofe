#include <SFML/Graphics.hpp>

class Cat 
{
    public:

        Cat(const std::string& spriteSheet);
        void move(float deltaTime);
        void attack(); 
        void draw(sf::RenderWindow& window);
 
    private:
        void Animation(float deltaTime);
        void Direction(int row);
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
        bool attacking_;              
        float attack_duration_;           
        float attack_timer_;
};