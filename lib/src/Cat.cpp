#include "Cat.hpp"
#include "Enemy.hpp"

Cat::Cat(const std::string& sprite_cat, const sf::Vector2f& initialPosition)
    : velocity_(0, 0),
      animation_time_(0),
      frame_duration_(0.1),  
      frame_count_(4),        
      current_row_(0),        
      moving_(false),      
      attacking_(false),
      attack_duration_(0.2),  
      attack_timer_(0.1)       
{
    texture_.loadFromFile(sprite_cat);
    frame_width_ = texture_.getSize().x / frame_count_;
    frame_height_ = texture_.getSize().y / frame_count_;       
    sprite_.setTexture(texture_);
    current_frame_ = sf::IntRect(0, 0, 28, 28);
    sprite_.setTextureRect(current_frame_);
    sprite_.setScale(2.5, 2.5); 
    sprite_.setPosition(initialPosition); 

    square_.setSize(sf::Vector2f(50, 50));
    square_.setFillColor(sf::Color::Red);

    size_ = sf::Vector2i(28, 28);
    bounding_square_.setFillColor(sf::Color::Transparent);
    bounding_square_.setOutlineColor(sf::Color::Transparent);
    bounding_square_.setOutlineThickness(1);
    bounding_square_.setSize(sf::Vector2f(size_.x * sprite_.getScale().x, size_.y * sprite_.getScale().y));
}   

bool Cat::isRectContained(const sf::FloatRect& outerRect, const sf::FloatRect& innerRect) {
    sf::Vector2f topLeft(innerRect.left, innerRect.top);
    sf::Vector2f topRight(innerRect.left + innerRect.width, innerRect.top);
    sf::Vector2f bottomLeft(innerRect.left, innerRect.top + innerRect.height);
    sf::Vector2f bottomRight(innerRect.left + innerRect.width, innerRect.top + innerRect.height);

    return outerRect.contains(topLeft) &&
           outerRect.contains(topRight) &&
           outerRect.contains(bottomLeft) &&
           outerRect.contains(bottomRight);
}

void Cat::Move(float deltaTime, const Map& room, Enemy& enemy) {
    velocity_ = sf::Vector2f(0, 0);
    moving_ = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        velocity_.y = -200;
        SetDirection(2);
        moving_ = true;
    } 
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        velocity_.y = 200;
        SetDirection(0);
        moving_ = true;
    } 
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocity_.x = -200;
        SetDirection(1);
        moving_ = true;
    } 
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocity_.x = 200;
        SetDirection(3);
        moving_ = true;
    }

    if (moving_) {
        
        sf::Vector2f newPosition = sprite_.getPosition() + (velocity_ * deltaTime);

        sf::FloatRect hitboxBounds = bounding_square_.getGlobalBounds();
        hitboxBounds.left = newPosition.x; 
        hitboxBounds.top = newPosition.y;

        sf::FloatRect mapBounds = room.GetBounds();

        if (isRectContained(mapBounds, hitboxBounds)) {

            sprite_.setPosition(newPosition);
            last_valid_position_ = newPosition; 

        } 
       
        bounding_square_.setPosition(sprite_.getPosition());

        Animate(deltaTime);
    } 
    else {
        current_frame_.left = 0; 
        sprite_.setTextureRect(current_frame_);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !attacking_) 
    {
        StartAttack();
    }
    Scratch(deltaTime, enemy);    

    bounding_square_.setPosition(sprite_.getPosition());
}

void Cat::Animate(float deltaTime) 
{
    animation_time_ += deltaTime;
    if (animation_time_ >= frame_duration_) 
    {
        animation_time_ = 0;
        current_frame_.left += frame_width_;
        if (current_frame_.left >= frame_width_ * frame_count_) 
        {
            current_frame_.left = 0; 
        }
        
        sprite_.setTextureRect(current_frame_); 
    }
}

void Cat::StartAttack() 
{
    attacking_ = true;
    attack_timer_ = 0;

    if (current_row_ == 0) { 
        square_.setPosition(sprite_.getPosition().x, sprite_.getPosition().y + 50);
        square_.setSize(sf::Vector2f(30, 30)); 
    } else if (current_row_ == 1) { 
        square_.setPosition(sprite_.getPosition().x - 50, sprite_.getPosition().y);
        square_.setSize(sf::Vector2f(30, 30));
    } else if (current_row_ == 2) {  
        square_.setPosition(sprite_.getPosition().x, sprite_.getPosition().y - 50);
        square_.setSize(sf::Vector2f(30, 30));
    } else if (current_row_ == 3) { 
        square_.setPosition(sprite_.getPosition().x + 50, sprite_.getPosition().y);
        square_.setSize(sf::Vector2f(30, 30));
    }
    square_.setFillColor(sf::Color::Transparent);
    square_.setOutlineColor(sf::Color::Blue); 
    square_.setOutlineThickness(2);
} 

void Cat::Scratch(float deltaTime, Enemy& enemy) 
{
    if (attacking_) {
        attack_timer_ += deltaTime;
        if (attack_timer_ >= attack_duration_) {
            attacking_ = false;  
        } else {
            if (square_.getGlobalBounds().intersects(enemy.GetHitbox())) {
                enemy.TakeDamage(10);  
            }
        }
    }
}

void Cat::SetDirection(int row) 
{
    if (current_row_ != row) 
    {
        current_row_ = row;
        current_frame_.top = current_row_ * frame_height_; 
        current_frame_.left = 0;  
        sprite_.setTextureRect(current_frame_);
    }
}

void Cat::Draw(sf::RenderWindow& window) 
{
    window.draw(bounding_square_);
    window.draw(sprite_);
    if (attacking_) 
    {
        window.draw(square_);  
    }    
}
