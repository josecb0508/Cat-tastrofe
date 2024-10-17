#include <SFML/Graphics.hpp>
#include "Cat.hpp"
#include "Map.hpp"
#include "Enemy.hpp"
#include <Menu.hpp>
 
int main()  
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Cat-tastrofe");
    Menu menu(1920,1080);
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
                    RenderWindow Play(VideoMode(1920,1080),"Play");
                    RenderWindow Exit(VideoMode(1920,1080),"Exit");

                    int x = menu.pressed();
                    if(x == 0)
                    {
                        while(Play.isOpen())
                        {
                            sf::Event event;
                            while(Play.pollEvent(event))
                            {
                                if(event.type == Event::Closed)
                                {
                                    Play.close();
                                }
                                if(event.type == Event::KeyPressed)
                                {
                                    if(event.key.code == Keyboard::Escape)
                                    {
                                        Play.close();
                                    }
                                }
                            }
                            float deltaTime = clock.restart().asSeconds();
                            Exit.close();
                            Play.clear(); 
                            cat.Move(deltaTime, room, enemy);
                            room.Draw(Play);

                            if (!enemy.IsDead())
                            {
                                enemy.Draw(Play);  
                            }

                            cat.Draw(Play);
                            Play.display();

                           window.clear();                           
                        }                           
                    }
                    if(x == 1)
                    {
                        Exit.close();
                        window.close();
                    }
                }
            }

        }

        window.clear();
        menu.draw(window);    
        window.display();
    }
    return 0;
}
