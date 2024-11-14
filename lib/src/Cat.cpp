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
      attack_duration_(0.4),  
      attack_timer_(0),
      max_hp_(100),
      current_hp_(100),
      strength_cat_(20),
      defense_Cat_(5)
{
    texture_.loadFromFile(sprite_cat);
    frame_width_ = 45;
    frame_height_ = 45;
    sprite_.setTexture(texture_);
    current_frame_ = sf::IntRect(0, 0, frame_width_, frame_height_);
    sprite_.setTextureRect(current_frame_);
    sprite_.setScale(1.8f, 1.8f);   
    sprite_.setPosition(initial_position);

    square_.setSize(sf::Vector2f(50, 50));
    square_.setFillColor(sf::Color::Red);

    size_ = sf::Vector2i(38, 38);
    bounding_square_.setFillColor(sf::Color::Transparent);
    bounding_square_.setOutlineColor(sf::Color::Transparent);
    bounding_square_.setOutlineThickness(1);
    bounding_square_.setSize(sf::Vector2f(size_.x * sprite_.getScale().x, size_.y * sprite_.getScale().y));
    hp_bar_background_.setSize(sf::Vector2f(100, 10)); 
    hp_bar_background_.setFillColor(sf::Color(100, 100, 100)); 
    hp_bar_background_.setPosition(10, 10); 

    hp_bar.setSize(sf::Vector2f(100, 10)); 
    hp_bar.setFillColor(sf::Color::Green);
    hp_bar.setPosition(10, 10);   
}

bool Cat::IsRectContained(const sf::FloatRect& outer_rect, const sf::FloatRect& inner_rect) {
    return outer_rect.contains(inner_rect.left, inner_rect.top) &&
           outer_rect.contains(inner_rect.left + inner_rect.width, inner_rect.top) &&
           outer_rect.contains(inner_rect.left, inner_rect.top + inner_rect.height) &&
           outer_rect.contains(inner_rect.left + inner_rect.width, inner_rect.top + inner_rect.height);
}

void Cat::GetDamage(float delta_time, Enemy& enemy)
{
    if (bounding_square_.getGlobalBounds().intersects(enemy.GetHitbox())) 
    {
        current_hp_ -= enemy.GetStrength()/defense_Cat_;
    }
        UpdateHealthBar();
}

float Cat::GetHealth()
{
    return current_hp_;
}

std::vector <Item> Cat::GetInventory()
{
    return items;
}


void Cat::AddItem(Item item)
{
    items.push_back(item);
}

void Cat::Move(float delta_time, Map& room, Enemy& enemy) {
    velocity_ = sf::Vector2f(0, 0);
    moving_ = false;

    int cellWidth = room.GetCellWidth();
    int cellHeight = room.GetCellHeight();
    sf::Vector2f position = sprite_.getPosition();
    int currentCellX = static_cast<int>(position.x / cellWidth);
    int currentCellY = static_cast<int>(position.y / cellHeight);

    // Detectar el movimiento deseado y ajustar velocidad sin limitar el movimiento
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        velocity_.y = -200;
        SetDirection(4);
        moving_ = true;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        velocity_.y = 200;
        SetDirection(0);
        moving_ = true;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocity_.x = -200;
        SetDirection(2);
        moving_ = true;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocity_.x = 200;
        SetDirection(6);
        moving_ = true;
    }

    // Si el gato está en movimiento, calculamos la nueva posición tentativamente
    if (moving_) {
        sf::Vector2f new_position = sprite_.getPosition() + (velocity_ * delta_time);
        sf::FloatRect hitbox_bounds = bounding_square_.getGlobalBounds();
        hitbox_bounds.left = new_position.x;
        hitbox_bounds.top = new_position.y;

        // Chequear colisiones solo si la nueva posición alcanza el borde de una celda `EMPTY`
        bool collision = false;

        // Verificación en cada dirección si se alcanzará una celda `EMPTY`
        if (velocity_.y < 0 && room.GetCellType(currentCellX, currentCellY - 1) == EMPTY) { // Arriba
            if (new_position.y < currentCellY * cellHeight) {
                new_position.y = currentCellY * cellHeight;
                collision = true;
            }
        } 
        else if (velocity_.y > 0 && room.GetCellType(currentCellX, currentCellY + 1) == EMPTY) { // Abajo
            if (new_position.y + bounding_square_.getSize().y > (currentCellY + 1) * cellHeight) {
                new_position.y = (currentCellY + 1) * cellHeight - bounding_square_.getSize().y;
                collision = true;
            }
        } 
        else if (velocity_.x < 0 && room.GetCellType(currentCellX - 1, currentCellY) == EMPTY) { // Izquierda
            if (new_position.x < currentCellX * cellWidth) {
                new_position.x = currentCellX * cellWidth;
                collision = true;
            }
        } 
        else if (velocity_.x > 0 && room.GetCellType(currentCellX + 1, currentCellY) == EMPTY) { // Derecha
            if (new_position.x + bounding_square_.getSize().x > (currentCellX + 1) * cellWidth) {
                new_position.x = (currentCellX + 1) * cellWidth - bounding_square_.getSize().x;
                collision = true;
            }
        }

        // Solo actualizar la posición si no hay colisión
        if (!collision && IsRectContained(room.GetBounds(), hitbox_bounds)) {
            sprite_.setPosition(new_position);
            last_valid_position_ = new_position;
        }

        bounding_square_.setPosition(sprite_.getPosition());

        if (moving_) {
            AnimateMovement(delta_time);
        }
    } else if (!attacking_) {
        ResetFrame();
    }

    // Control de ataque y otros comportamientos
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !attacking_) {
        StartAttack();
    } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::X) && attacking_) {
        attacking_ = false;
        current_row_ = direction_before_attack_;
        ResetFrame();
    }
    Scratch(delta_time, enemy);
    if (attacking_) {
        AnimateAttack(delta_time);
    }
    GetDamage(delta_time, enemy);

    // Intersección con ítem en la habitación
    if(sprite_.getGlobalBounds().intersects(room.GetRandomItem().GetGlobalBounds()))
    {
        room.SetItemIntersected(true);
        if (!room.GetItemCollected() && itemCounter_ < itemLimit_) 
        {
            itemCounter_++;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && itemCounter_ >= itemLimit_ && !room.GetItemCollected())
        {
            itemCounter_ = 0;
            room.SetItemCollected(true);
            AddItem(room.GetRandomItem());
        }
    }
}

void Cat::AnimateMovement(float delta_time) {
    animation_time_ += delta_time;

    if (animation_time_ >= frame_duration_) {
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
    direction_before_attack_ = current_row_;  
    if (current_row_ == 6) {  
        current_row_ = 11;
        square_.setSize(sf::Vector2f(20, 60));
        square_.setPosition(sprite_.getPosition().x + frame_width_ * sprite_.getScale().x - 8, sprite_.getPosition().y + (size_.y / 4) * sprite_.getScale().y);
    } else if (current_row_ == 2) {  
        current_row_ = 9;
        square_.setSize(sf::Vector2f(20, 60));
        square_.setPosition(sprite_.getPosition().x - 10, sprite_.getPosition().y + (size_.y / 4) * sprite_.getScale().y);
    } else if (current_row_ == 0) { 
        current_row_ = 8;
        square_.setSize(sf::Vector2f(50, 20));
        square_.setPosition(sprite_.getPosition().x + (size_.x / 4) * sprite_.getScale().x, sprite_.getPosition().y + frame_height_ * sprite_.getScale().y - 8);
    } else if (current_row_ == 4) {  
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

void Cat::AnimateAttack(float delta_time) {
    attack_timer_ += delta_time;
    if (attack_timer_ >= attack_duration_) {
        attacking_ = false;
        current_row_ = direction_before_attack_; 
    } else {
        animation_time_ += delta_time;
        if (animation_time_ >= frame_duration_) {
            animation_time_ = 0;
            current_frame_.left += frame_width_;
            if (current_frame_.left >= frame_width_ * frame_count_) {
                current_frame_.left = 0;
            }
            sprite_.setTextureRect(current_frame_);
        }
    }
}

void Cat::Scratch(float delta_time, Enemy& enemy) 
{
    if (attacking_) 
    {
        AnimateAttack(delta_time);
        if (square_.getGlobalBounds().intersects(enemy.GetHitbox())) {
            enemy.TakeDamage(strength_cat_);
        }
    }
}
void Cat::SetPosition(const sf::Vector2f& position) {
    sprite_.setPosition(position);
    bounding_square_.setPosition(position);
}

sf::Vector2f Cat::GetPosition() const 
{
    return sprite_.getPosition(); 
}

void Cat::SetDirection(int row) {
    if (current_row_ != row && !attacking_) {  
        current_row_ = row;
        ResetFrame();
    }
}

void Cat::ResetFrame() {
    current_frame_.top = current_row_ * frame_height_;
    current_frame_.left = 0;
    sprite_.setTextureRect(current_frame_);
}

void Cat::UpdateHealthBar() 
{      
    float hp_percentage = current_hp_ / max_hp_;
    hp_bar.setSize(sf::Vector2f(100 * hp_percentage, 10));
}

void Cat::DrawHealthBar(sf::RenderWindow& window){
    window.draw(hp_bar_background_); 
    window.draw(hp_bar); 
}

sf::Vector2f Cat::GetHealthBarPosition() const {
    return hp_bar_background_.getPosition(); 
}
void Cat::Draw(sf::RenderWindow& window) { 
    window.draw(bounding_square_);
    window.draw(sprite_);
    if (attacking_) {
        window.draw(square_);
    }
}
