#include "Cat.hpp"
#include "Enemy.hpp"

Cat::Cat(const std::string& sprite_cat, const sf::Vector2f& initial_position)
    : velocity_(0, 0),
      animation_time_(0),
      frame_duration_(0.1),  
      frame_count_(4),        
      current_row_(0),        
      moving_(false),      
      attacking_(false),
      attack_duration_(0.1),  
      attack_timer_(0)       
{
    texture_.loadFromFile(sprite_cat);
    frame_width_ = 45;
    frame_height_ = 45;    
    sprite_.setTexture(texture_);
    current_frame_ = sf::IntRect(0, 0, 45, 45);
    sprite_.setTextureRect(current_frame_);
    sprite_.setScale(2.5f, 2.5f); 
    sprite_.setPosition(initial_position); 

    square_.setSize(sf::Vector2f(50, 50));
    square_.setFillColor(sf::Color::Red);

    size_ = sf::Vector2i(45, 45);
    bounding_square_.setFillColor(sf::Color::Transparent);
    bounding_square_.setOutlineColor(sf::Color::Transparent);
    bounding_square_.setOutlineThickness(1);
    bounding_square_.setSize(sf::Vector2f(size_.x * sprite_.getScale().x, size_.y * sprite_.getScale().y));
}   

bool Cat::IsRectContained(const sf::FloatRect& outer_rect, const sf::FloatRect& inner_rect) {
    sf::Vector2f top_left(inner_rect.left, inner_rect.top);
    sf::Vector2f top_right(inner_rect.left + inner_rect.width, inner_rect.top);
    sf::Vector2f bottom_left(inner_rect.left, inner_rect.top + inner_rect.height);
    sf::Vector2f bottom_right(inner_rect.left + inner_rect.width, inner_rect.top + inner_rect.height);

    return outer_rect.contains(top_left) &&
           outer_rect.contains(top_right) &&
           outer_rect.contains(bottom_left) &&
           outer_rect.contains(bottom_right);
}

void Cat::Move(float delta_time, const Map& room, Enemy& enemy) {
    if (!attacking_) {
        velocity_ = sf::Vector2f(0, 0);
        moving_ = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            velocity_.y = -200;
            SetDirection(4);
            moving_ = true;
        } 
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            velocity_.y = 200;
            SetDirection(0);
            moving_ = true;
        } 
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            velocity_.x = -200;
            SetDirection(2);
            moving_ = true;
        } 
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            velocity_.x = 200;
            SetDirection(6);
            moving_ = true;
        }

        if (moving_) {
            sf::Vector2f new_position = sprite_.getPosition() + (velocity_ * delta_time);
            sf::FloatRect hitbox_bounds = bounding_square_.getGlobalBounds();
            hitbox_bounds.left = new_position.x; 
            hitbox_bounds.top = new_position.y;

            sf::FloatRect map_bounds = room.GetBounds();
            if (IsRectContained(map_bounds, hitbox_bounds)) {
                sprite_.setPosition(new_position);
                last_valid_position_ = new_position;
            } 

            bounding_square_.setPosition(sprite_.getPosition());
            Animate(delta_time);
        } else {
            current_frame_.left = 0;
            sprite_.setTextureRect(current_frame_);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !attacking_) {
        StartAttack();
    }

    Scratch(delta_time, enemy);    
    bounding_square_.setPosition(sprite_.getPosition());
}

void Cat::Animate(float delta_time) {
    animation_time_ += delta_time;

    if (attacking_) {
        attack_timer_ += delta_time;

        if (attack_timer_ >= attack_duration_) {
            attacking_ = false; 
            current_row_ = 0;  
            current_frame_.top = current_row_ * frame_height_;
            current_frame_.left = 0; 
        } else if (animation_time_ >= frame_duration_) {
            animation_time_ = 0;
            current_frame_.left += frame_width_;
            if (current_frame_.left >= frame_width_ * 4) {  
                current_frame_.left = 0;  
            }
            sprite_.setTextureRect(current_frame_);
        }
    } 
    else if (animation_time_ >= frame_duration_) {
        animation_time_ = 0;
        current_frame_.left += frame_width_;
        if (current_frame_.left >= frame_width_ * frame_count_) {
            current_frame_.left = 0;  
        }
        sprite_.setTextureRect(current_frame_);
    }
}

void Cat::StartAttack() {
    attacking_ = true;   
    attack_timer_ = 0;   

    if (current_row_ == 6) 
    {       
        current_row_ = 11;         
        square_.setSize(sf::Vector2f(20, 60));
        square_.setPosition(sprite_.getPosition().x + frame_width_ * sprite_.getScale().x - 8, sprite_.getPosition().y + (size_.y / 4) * sprite_.getScale().y);
    } else if (current_row_ == 2) 
    { 
        current_row_ = 9;         
        square_.setSize(sf::Vector2f(20, 60)); 
        square_.setPosition(sprite_.getPosition().x - 10, sprite_.getPosition().y + (size_.y / 4) * sprite_.getScale().y);
    } else if (current_row_ == 0) 
    {
        current_row_ = 8;         
        square_.setSize(sf::Vector2f(50, 20)); 
        square_.setPosition(sprite_.getPosition().x + (size_.x / 4) * sprite_.getScale().x, sprite_.getPosition().y + frame_height_ * sprite_.getScale().y - 8);
    } else if (current_row_ == 4) 
    { 
        current_row_ = 10;         
        square_.setSize(sf::Vector2f(50, 20)); 
        square_.setPosition(sprite_.getPosition().x + (size_.x / 4) * sprite_.getScale().x, sprite_.getPosition().y - 10);
    }

    current_frame_.top = current_row_ * frame_height_;  
    current_frame_.left = 0;                           
    sprite_.setTextureRect(current_frame_);  
    square_.setFillColor(sf::Color::Transparent);  
    square_.setOutlineColor(sf::Color::Transparent);
    square_.setOutlineThickness(2);
} 

void Cat::Scratch(float delta_time, Enemy& enemy) {
    if (attacking_) {
        attack_timer_ += delta_time;
        animation_time_ += delta_time;

        if (animation_time_ >= frame_duration_) {
            animation_time_ = 0;
            current_frame_.left += frame_width_; 

            if (current_frame_.left >= frame_width_ * 4) {
                current_frame_.left = 0;  
                attacking_ = false;

                if (current_row_ == 9) {        
                    current_row_ = 2;           
                } else if (current_row_ == 11) { 
                    current_row_ = 6;          
                } else if (current_row_ == 8) {  
                    current_row_ = 0;           
                } else if (current_row_ == 10) {
                    current_row_ = 4;          
                }

                current_frame_.top = current_row_ * frame_height_;
                current_frame_.left = 0;
            }

            sprite_.setTextureRect(current_frame_);

            if (square_.getGlobalBounds().intersects(enemy.GetHitbox())) {
                enemy.TakeDamage(10);  
            }
        }
    }
}

void Cat::SetDirection(int row) {
    if (current_row_ != row) {
        current_row_ = row;
        current_frame_.top = current_row_ * frame_height_; 
        current_frame_.left = 0;  
        sprite_.setTextureRect(current_frame_);
    }
}

void Cat::Draw(sf::RenderWindow& window) {
    window.draw(bounding_square_);
    window.draw(sprite_);
    if (attacking_) {
        window.draw(square_);  
    }    
}