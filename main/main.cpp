#include <SFML/Graphics.hpp>
#include <Cat.hpp>

int main() 
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cat-tastrofe");
    window.setFramerateLimit(60);

    Cat cat("resources/cat.png");

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
        cat.move(deltaTime); 
        window.clear();
        cat.draw(window);    
        window.display();
    }
    return 0;
}
