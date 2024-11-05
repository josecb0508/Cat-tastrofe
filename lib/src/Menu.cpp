#include <Menu.hpp>
#include "MenuPauseState.hpp"
using namespace std;
using namespace sf; 

Menu::Menu(stack<State*> *state_stack, RenderWindow* window, float width, float height)
    : State(state_stack, window)
{
    Init();
}

Menu::~Menu() {}

void Menu::Init() {
    if (!texture.loadFromFile("resources/ciudad.png")) 
    {
        throw "Error al cargar la textura";
    }

    menu_sprite.setTexture(texture);
    font.loadFromFile("resources/Silkscreen-Regular.ttf");
    
    mainmenu[0].setFont(font);
    mainmenu[0].setFillColor(Color{225, 204, 0});
    mainmenu[0].setString("Play");
    mainmenu[0].setCharacterSize(60);
    mainmenu[0].setPosition(Vector2f((800 - mainmenu[0].getGlobalBounds().width) / 2, 600 / 4));

    mainmenu[1].setFont(font);
    mainmenu[1].setFillColor(Color::White);
    mainmenu[1].setString("Exit");
    mainmenu[1].setCharacterSize(60);
    mainmenu[1].setPosition(Vector2f((800 - mainmenu[0].getGlobalBounds().width) / 2, 600 / 4 + 50));

    selected = 0;  
}

void Menu::SetSelected(int n)
{
    selected = n;
}

void Menu::ProcessInput(sf::Event& event)
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
        else if (event.key.code == sf::Keyboard::Return) 
        {
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

void Menu::Update(const float& deltaTime)
{
}

void Menu::Draw(sf::RenderWindow* window)
{
    window->draw(menu_sprite);
    for (int i = 0; i < 2; i++)
    {
        window->draw(mainmenu[i]);
    }
}

void Menu::MoveDown()
{
    if (selected + 1 <= 2)
    {
        mainmenu[selected].setFillColor(Color::White);
        selected++;
        if (selected == 2)
        {
            selected = 0;
        }
        mainmenu[selected].setFillColor(Color{255, 204, 0});
    }
}

void Menu::MoveUp()
{
    if (selected - 1 >= -1)
    {
        mainmenu[selected].setFillColor(Color::White);
        selected--;
        if (selected == -1)
        {
            selected = 2;
        }
        mainmenu[selected].setFillColor(Color{255, 204, 0});
    }
}
