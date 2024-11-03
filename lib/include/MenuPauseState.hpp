#pragma once
#include "State.hpp"
#include <stack>

using namespace std;
using namespace sf;

class MenuPauseState : public State
{
public:
    MenuPauseState(std::stack<State*>* state_stack, sf::RenderWindow* window);
    void Init() override;
    void Draw(sf::RenderWindow* window = nullptr) override;
    void SetSelected(int n);
    void ProcessInput(sf::Event& event) override;
    void HandleMouseInput(Vector2i mousePosition);
    void Update(const float& deltaTime) override;
    ~MenuPauseState();

private:
    sf::Text pauseMenu[3]; 
    sf::Font font;
    sf::Sprite menu_pause;
    sf::Texture texture;
    int selected;
    void MoveUp();
    void MoveDown();
    int Pressed() const { return selected; }
};
