#include <Menu.hpp>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf; 

Menu::Menu(float width,float heigth)
{
    font.loadFromFile("C:\\Users\\aacmq\\OneDrive\\Documentos\\Animus\\Cat-tastrofe\\resources\\Silkscreen-Regular.ttf"); 

    mainmenu[0].setFont(font);
    mainmenu[0].setFillColor(Color{225,204,0});
    mainmenu[0].setString("Play");
    mainmenu[0].setCharacterSize(60);
    mainmenu[0].setPosition(Vector2f(
        (width - mainmenu[0].getGlobalBounds().width)/ 2, 
        heigth / (4)));

    mainmenu[1].setFont(font);
    mainmenu[1].setFillColor(Color::White);
    mainmenu[1].setString("Exit");
    mainmenu[1].setCharacterSize(60);
    mainmenu[1].setPosition(Vector2f(
        (width - mainmenu[0].getGlobalBounds().width) / 2, 
        heigth / (4)+50));

    selected = 0;
}

Menu::~Menu(){}

void Menu::setSelected(int n)
{
    selected = n;
}

void Menu::draw(RenderWindow& window)
{
    for(int i= 0; i < 2; i++)
    {
        window.draw(mainmenu[i]);
        
    }

}

void Menu::MoveDown()
{
    if(selected + 1 <= 2)
    {
        mainmenu[selected].setFillColor(Color::White);
        selected++;
        if (selected == 2)
        {
            selected = 0;
        }
        mainmenu[selected].setFillColor(Color{255,204,0});
    }
}

void Menu::Moveup()
{
    if(selected -1 >= -1)
    {
        mainmenu[selected].setFillColor(Color::White);
        selected--;
        if (selected == -1)
        {
            selected = 2;
        }
        mainmenu[selected].setFillColor(Color{255,204,0});
    }
}