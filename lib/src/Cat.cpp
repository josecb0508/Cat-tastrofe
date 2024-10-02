#include </home/jose/Descargas/Cat-tastrofe-Cat-tastrofe/lib/include/Cat.hpp>

Cat::Cat(const std::string& sprite_cat)
    : velocity(0.f, 0.f),
      animationTime(0.f),
      frameDuration(0.1f),  
      frameCount(4),        
      currentRow(0),       
      isMoving(false)      
{
    texture.loadFromFile(sprite_cat);

    frameWidth = texture.getSize().x / frameCount;
    frameHeight = texture.getSize().y / frameCount;       

    sprite.setTexture(texture);
    currentFrame = sf::IntRect(28, 28, 28, 28);
    sprite.setTextureRect(currentFrame);
    sprite.setScale(3.f, 3.f);
}

void Cat::move(float deltaTime) 
{
    velocity = sf::Vector2f(0.f, 0.f);
    isMoving = false;  

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
    {
        velocity.y = -200.f;
        setDirection(2); 
        isMoving = true;
    } 
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
    {
        velocity.y = 200.f;
        setDirection(0); 
        isMoving = true;
    } 
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
    {
        velocity.x = -200.f;
        setDirection(1); 
        isMoving = true;
    } 
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
    {
        velocity.x = 200.f;
        setDirection(3); 
        isMoving = true;
    }

    if (isMoving) 
    {
        sprite.move(velocity * deltaTime);
        updateAnimation(deltaTime);
    } else 
    {
        currentFrame.left = 0;
        sprite.setTextureRect(currentFrame);
    }
}

void Cat::updateAnimation(float deltaTime) 
{
    animationTime += deltaTime;

    
    if (animationTime >= frameDuration) 
    {
        animationTime = 0.f;

        currentFrame.left += frameWidth;
        if (currentFrame.left >= frameWidth * frameCount) 
        {
            currentFrame.left = 0; 
        }
        
        sprite.setTextureRect(currentFrame); 
    }
}

void Cat::setDirection(int row) 
{
    if (currentRow != row) 
    {
        currentRow = row;
        currentFrame.top = currentRow * frameHeight; 
        currentFrame.left = 0;  
        sprite.setTextureRect(currentFrame);
    }
}

void Cat::draw(sf::RenderWindow& window) 
{
    window.draw(sprite);
}