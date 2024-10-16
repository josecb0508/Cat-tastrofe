#include "Cat.hpp"

Cat::Cat(const std::string& sprite_cat, const sf::Vector2f& initialPosition)
    : velocity_(0, 0),
      animation_time_(0),
      frame_duration_(0.1),  
      frame_count_(4),        
      current_row_(0),       
      moving_(false),      
      attacking_(false),
      attack_duration_(0.5),  
      attack_timer_(0.1)       
{
    texture_.loadFromFile(sprite_cat);
    frame_width_ = texture_.getSize().x / frame_count_;
    frame_height_ = texture_.getSize().y / frame_count_;       
    sprite_.setTexture(texture_);
    current_frame_ = sf::IntRect(0, 0, 28, 28);
    sprite_.setTextureRect(current_frame_);
    sprite_.setScale(1.5, 1.5); 
    sprite_.setPosition(initialPosition); 

    square_.setSize(sf::Vector2f(50, 50));
    square_.setFillColor(sf::Color::Red);

    size_ = sf::Vector2i(30, 30); // Hitbox size
    /*bounding_square_.setFillColor(sf::Color::Transparent);
    bounding_square_.setOutlineColor(sf::Color::Red);
    bounding_square_.setOutlineThickness(1);*/
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

void Cat::move(float deltaTime, const Map& room) {
    velocity_ = sf::Vector2f(0, 0);
    moving_ = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        velocity_.y = -200;
        Direction(2);
        moving_ = true;
    } 
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        velocity_.y = 200;
        Direction(0);
        moving_ = true;
    } 
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocity_.x = -200;
        Direction(1);
        moving_ = true;
    } 
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocity_.x = 200;
        Direction(3);
        moving_ = true;
    }

    if (moving_) {
        
        sf::Vector2f newPosition = sprite_.getPosition() + (velocity_ * deltaTime);

        sf::FloatRect hitboxBounds = bounding_square_.getGlobalBounds();
        hitboxBounds.left = newPosition.x; 
        hitboxBounds.top = newPosition.y;

        sf::FloatRect mapBounds = room.getBounds();

        if (isRectContained(mapBounds, hitboxBounds)) {

            sprite_.setPosition(newPosition);
            last_valid_position_ = newPosition; 

        } 
       
        bounding_square_.setPosition(sprite_.getPosition());

        Animation(deltaTime);
    } 
    else {
        current_frame_.left = 0; 
        sprite_.setTextureRect(current_frame_);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !attacking_) 
    {
        attack();
    }
    Attack_Cat(deltaTime);    

    bounding_square_.setPosition(sprite_.getPosition());
}

void Cat::Animation(float deltaTime) 
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

void Cat::attack() 
{
    attacking_ = true;
    attack_timer_ = 0;

    if (current_row_ == 0)  
    {
        square_.setPosition(sprite_.getPosition().x, sprite_.getPosition().y + 100);
    }
    
    else if (current_row_ == 1)  
    {
        square_.setPosition(sprite_.getPosition().x - 60, sprite_.getPosition().y);
    }

    else if (current_row_ == 2)  
    {
        square_.setPosition(sprite_.getPosition().x, sprite_.getPosition().y - 60);
    }

    else if (current_row_ == 3) 
    {
        square_.setPosition(sprite_.getPosition().x + 100, sprite_.getPosition().y);
    }
} 

void Cat::Attack_Cat(float deltaTime) 
{
    if (attacking_) 
    {
        attack_timer_ += deltaTime;
        if (attack_timer_ >= attack_duration_) 
        {
            attacking_ = false; 
        }
    }
}

void Cat::Direction(int row) 
{
    if (current_row_ != row) 
    {
        current_row_ = row;
        current_frame_.top = current_row_ * frame_height_; 
        current_frame_.left = 0;  
        sprite_.setTextureRect(current_frame_);
    }
}

void Cat::draw(sf::RenderWindow& window) 
{
    //window.draw(bounding_square_);
    window.draw(sprite_);
    if (attacking_) 
    {
        window.draw(square_);  
    }    
}
