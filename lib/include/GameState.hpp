#include "State.hpp"
#include "Cat.hpp"
#include "Map.hpp"
#include "Enemy.hpp"
#include "Golem.hpp"

class GameState : public State
{
public:
    GameState(std::stack<State*>* state_stack, sf::RenderWindow* window);
    void Init() override; // Make sure to override
    void ProcessInput(sf::Event& event) override; // Make sure to override
    void Update(const float& deltaTime) override; // Make sure to override
    void Draw(sf::RenderWindow* window = nullptr) override; // Make sure to override
    ~GameState();

private:
    int current_level;
    Cat cat;
    Golem golem;
    Map room;
};
