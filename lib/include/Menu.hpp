#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Menu
{
public :
    Text mainmenu[2]; 
    Menu(float with,float heigth);
    void draw(RenderWindow& Window);
    void Moveup();
    void MoveDown();
    void setSelected(int n);
    int pressed() {
        return selected;
    }
    ~Menu();  

private :
    int selected;
    Font font;

};
