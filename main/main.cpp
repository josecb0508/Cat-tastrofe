#include <SFML/Graphics.hpp>
#include "Cat.hpp"
#include "Map.hpp"

int main() 
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cat-tastrofe");
    window.setFramerateLimit(60);

    Map room(600, 400);

    sf::Vector2f initialPosition(
        room.getBounds().left + (room.getBounds().width / 2) - (30 * 1.5 / 2), 
        room.getBounds().top + (room.getBounds().height / 2) - (30 * 1.5 / 2)
    );

    Cat cat("C:\\Users\\aacmq\\OneDrive\\Escritorio\\CC0X_PR3\\Cat-tastrofe\\resources\\cat.png", initialPosition);

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
        cat.move(deltaTime, room);

        window.clear();
        room.draw(window);
        cat.draw(window);
        window.display();
    }
    return 0;
}
