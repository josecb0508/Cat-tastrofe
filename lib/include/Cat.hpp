#include <SFML/Graphics.hpp>

class Cat 
{
    public:

        Cat(const std::string& spriteSheetPath);
        void move(float deltaTime);
        void draw(sf::RenderWindow& window);

    private:
        sf::Texture texture;      
        sf::Sprite sprite;       
        sf::Vector2f velocity;    
        sf::IntRect currentFrame; 
        float animationTime;      
        float frameDuration;      
        int currentRow;           
        int frameCount;         
        int frameWidth;          
        int frameHeight;         
        bool isMoving;
        void updateAnimation(float deltaTime);
        void setDirection(int row);
};