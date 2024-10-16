#include <SFML/Graphics.hpp>
#include "Cat.hpp"
#include "Map.hpp"
#include "Enemy.hpp"
 
int main()  
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Cat-tastrofe");
    window.setFramerateLimit(60);

    Map room(1920, 1080);

sf::Vector2f initialPosition(
    room.GetBounds().width / 2 - (30 * 1.5 / 2), 
    room.GetBounds().height / 2 - (30 * 1.5 / 2)
);
    Cat cat("resources/cat.png", initialPosition);
    Enemy enemy("resources/enemy.png", sf::Vector2f(850, 600), 200);

    sf::Clock clock; 

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
        }

        float deltaTime = clock.restart().asSeconds();
        cat.Move(deltaTime, room, enemy);

        window.clear();
        room.Draw(window);
    if (!enemy.IsDead()) {
        enemy.Draw(window);  
    }

        cat.Draw(window);
        window.display();
    }
    return 0;
}
