#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include <stack>

using namespace std;
using namespace sf;

class Menu : public State
{
public:
    Menu(std::stack<State*> *state_stack, sf::RenderWindow* window, float width, float height);
    void Init() override;  // Agregado
    void Draw(sf::RenderWindow* window = nullptr) override;
    void MoveUp();
    void MoveDown();
    void SetSelected(int n);
    void ProcessInput(sf::Event& event);
    void Update(const float& deltaTime) override;
    int Pressed() const {
        return selected;
    }
    ~Menu();

private:
    Text mainmenu[2];
    sf::Sprite menu_sprite;
    sf::Texture texture;
    int selected;
    Font font;
};