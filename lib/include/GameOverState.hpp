#pragma once
#include "State.hpp"
#include <stack>

using namespace std;
using namespace sf;

class GameOverState : public State
{
public:
    GameOverState(std::stack<State*>* state_stack, sf::RenderWindow* window);
    void Init() override;
    void Draw(sf::RenderWindow* window = nullptr) override;
    void SetSelected(int n);
    void ProcessInput(sf::Event& event) override;
    void Update(const float& deltaTime) override;
    ~GameOverState();

private:
    sf::Text gameOver[2]; 
    sf::Text title;
    sf::Font font;
    sf::Sprite game_over;
    sf::Texture texture;
    int selected;
    void MoveUp();
    void MoveDown();
    int Pressed() const { return selected; }
};
