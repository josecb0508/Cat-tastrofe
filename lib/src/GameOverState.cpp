#include "GameOverState.hpp"
#include "Menu.hpp"

using namespace std;
using namespace sf;

GameOverState::GameOverState(std::stack<State*>* state_stack, sf::RenderWindow* window)
    : State(state_stack, window)
{
    Init();
}

GameOverState::~GameOverState() {}

void GameOverState::Init()
{
    if (!texture.loadFromFile(".\\resources\\ciudad.png")) 
    {
        throw "Error al cargar la textura";
    }

    game_over.setTexture(texture);
    font.loadFromFile(".\\resources\\Silkscreen-Regular.ttf");

    title.setFont(font);
    title.setFillColor(Color{225, 204, 0});
    title.setString("GAME OVER");
    title.setCharacterSize(60);
    title.setPosition(Vector2f((800 - title.getGlobalBounds().width) / 2,75));

    gameOver[0].setFont(font);
    gameOver[0].setFillColor(Color{225, 204, 0});
    gameOver[0].setString("Retry");
    gameOver[0].setCharacterSize(60);
    gameOver[0].setPosition(Vector2f((800 - gameOver[0].getGlobalBounds().width) / 2, 600 / 4));

    gameOver[1].setFont(font);
    gameOver[1].setFillColor(Color::White);
    gameOver[1].setString("Exit");
    gameOver[1].setCharacterSize(60);
    gameOver[1].setPosition(Vector2f((800 - gameOver[1].getGlobalBounds().width) / 2, 600 / 4 + 50));

    selected = 0;
}

void GameOverState::SetSelected(int n)
{
    selected = n;
}

void GameOverState::ProcessInput(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Down) 
        {
            MoveDown();
        }
        else if (event.key.code == sf::Keyboard::Up) {
            MoveUp();
        }
        else if (event.key.code == sf::Keyboard::Return) {
            int x = Pressed();
            if (x == 0) 
            {
                state_stack->push(new GameState(state_stack, window));
            }
            else if (x == 1) 
            {
                window->close();
            }
        }
    }
}

void GameOverState::Update(const float& deltaTime)
{
}

void GameOverState::Draw(sf::RenderWindow* window)
{
    window->draw(game_over);
    for (int i = 0; i < 3; i++)
    {
        window->draw(gameOver[i]);
    }
}

void GameOverState::MoveDown()
{
    if (selected + 1 < 2)
    {
        gameOver[selected].setFillColor(Color::White);
        selected++;
        if (selected == 3)
        {
            selected = 0;
        }
        gameOver[selected].setFillColor(Color{255, 204, 0});
    }
}

void GameOverState::MoveUp()
{
    if (selected - 1 >= -1)
    {
        gameOver[selected].setFillColor(Color::White);
        selected--;
        if (selected == -1)
        {
            selected = 3;
        }
        gameOver[selected].setFillColor(Color{255, 204, 0});
    }
}
