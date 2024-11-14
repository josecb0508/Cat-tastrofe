#ifndef GAME_HPP
#define GAME_HPP
#include "State.hpp"
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
    ~Game();  

private:
    sf::RenderWindow *window;
    std::stack<State*> state_stack;
    sf::RectangleShape rect;
    sf::Texture texture;
    sf::Clock clock;
    float deltaTime;

    void InitGame();
    void HandleEvents();
    void Update();
    void Draw();
};
#endif 
