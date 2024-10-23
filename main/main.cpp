#include <SFML/Graphics.hpp>
#include "Cat.hpp"
#include "Map.hpp"
#include "Enemy.hpp"
#include <Menu.hpp>
 
int main()  
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cat-tastrofe");
    Menu menu(800,600);
    int current_level = 2;
    window.setFramerateLimit(60);

    sf::RectangleShape rect(sf::Vector2f(200, 100));
    rect.setSize(sf::Vector2f(800, 600));
    Map room(800, 600, current_level);

    sf::Vector2f initialPosition(
        room.GetBounds().width / 2 - (30 * 1.5 / 2), 
        room.GetBounds().height / 2 - (30 * 1.5 / 2)
    );

    Cat cat("resources/cat.png", initialPosition);
    Enemy enemy("resources/enemy.png", sf::Vector2f(380, 250), 200);

    
    sf::Texture texture;
    if (!texture.loadFromFile("resources/ciudad.png"))
    {
        throw "Error al cargar la textura";
        return -1;
    }

    sf::Texture* _texture = new sf::Texture(texture);

    rect.setTexture(_texture);
  
    
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
            if(event.type == Event::KeyPressed)
            {
                if(event.key.code == Keyboard::Down)
                {
                    menu.MoveDown();
                }
                if(event.key.code == Keyboard::Up)
                {
                    menu.Moveup();
                }
                if(event.key.code == Keyboard::Return)
                {
                    
                    int x = menu.pressed();

                    if(x == 0)
                    {
                        while(window.isOpen())
                        {
                            float deltaTime = clock.restart().asSeconds();
                            window.clear(); 
                            cat.Move(deltaTime, room, enemy);
                            room.Draw(window);

                            if (!enemy.IsDead())
                            {
                                enemy.Draw(window);  
                            }

                            cat.Draw(window);
                            window.display();

                           window.clear();                           
                        }                           
                    }
                    if(x == 1)
                    {
                        window.close();
                    }
                }
            }

        }

        window.clear();
        window.draw(rect);
        menu.draw(window);    
        window.display();
    }
    return 0;
}
