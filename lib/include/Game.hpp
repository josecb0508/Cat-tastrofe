#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Cat.hpp"
#include "Map.hpp"
#include "Enemy.hpp"
#include "Menu.hpp"
#include "Golem.hpp"

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    Menu menu;
    int current_level;
    Cat cat;
    Golem golem;
    Map room;
    sf::RectangleShape rect;
    sf::Texture texture;
    sf::Clock clock;

    void initGame();
    void handleEvents();
    void handleMenuInput(const sf::Event& event);
    void startGameLoop();
    void update();
};

#endif // GAME_HPP
