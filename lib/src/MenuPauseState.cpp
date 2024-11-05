#include "MenuPauseState.hpp"
#include "Menu.hpp"

using namespace std;
using namespace sf;

MenuPauseState::MenuPauseState(std::stack<State*>* state_stack, sf::RenderWindow* window)
    : State(state_stack, window)
{
    Init();
}

MenuPauseState::~MenuPauseState() {}

void MenuPauseState::Init()
{
    if (!texture.loadFromFile("resources/ciudad.png")) 
    {
        throw "Error al cargar la textura";
    }

    menu_pause.setTexture(texture);
    font.loadFromFile("resources/Silkscreen-Regular.ttf");

    pauseMenu[0].setFont(font);
    pauseMenu[0].setFillColor(Color{225, 204, 0});
    pauseMenu[0].setString("Continue");
    pauseMenu[0].setCharacterSize(60);
    pauseMenu[0].setPosition(Vector2f((800 - pauseMenu[0].getGlobalBounds().width) / 2, 600 / 4));

    pauseMenu[1].setFont(font);
    pauseMenu[1].setFillColor(Color::White);
    pauseMenu[1].setString("Menu");
    pauseMenu[1].setCharacterSize(60);
    pauseMenu[1].setPosition(Vector2f((800 - pauseMenu[1].getGlobalBounds().width) / 2, 600 / 4 + 50));

    pauseMenu[2].setFont(font);
    pauseMenu[2].setFillColor(Color::White);
    pauseMenu[2].setString("Exit");
    pauseMenu[2].setCharacterSize(60);
    pauseMenu[2].setPosition(Vector2f((800 - pauseMenu[2].getGlobalBounds().width) / 2, 600 / 4 + 100));

    selected = 0;
}

void MenuPauseState::SetSelected(int n)
{
    selected = n;
}

void MenuPauseState::ProcessInput(sf::Event& event)
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
                state_stack->pop();
            }
            else if (x == 1) 
            {
                state_stack->push(new Menu(state_stack, window, 800, 600));
            }
            else if(x == 2)
            {
                window->close();
            }
        }
    }
}

void MenuPauseState::Update(const float& deltaTime)
{
}

void MenuPauseState::Draw(sf::RenderWindow* window)
{
    window->draw(menu_pause);
    for (int i = 0; i < 3; i++)
    {
        window->draw(pauseMenu[i]);
    }
}

void MenuPauseState::MoveDown()
{
    if (selected + 1 < 3)
    {
        pauseMenu[selected].setFillColor(Color::White);
        selected++;
        if (selected == 3)
        {
            selected = 0;
        }
        pauseMenu[selected].setFillColor(Color{255, 204, 0});
    }
}

void MenuPauseState::MoveUp()
{
    if (selected - 1 >= -1)
    {
        pauseMenu[selected].setFillColor(Color::White);
        selected--;
        if (selected == -1)
        {
            selected = 3;
        }
        pauseMenu[selected].setFillColor(Color{255, 204, 0});
    }
}
