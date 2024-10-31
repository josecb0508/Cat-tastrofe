#ifndef STATE_HPP
#define STATE_HPP
#include <SFML/Graphics.hpp>
#include <stack>

class State
{
public:
    State(std::stack<State*> *state_stack, sf::RenderWindow* window);
    virtual ~State(){}; // Virtual destructor

    virtual void Init() = 0; // Make it pure virtual
    virtual void ProcessInput(sf::Event& event) = 0; // Pure virtual
    virtual void Update(const float& deltaTime) = 0; // Pure virtual
    virtual void Draw(sf::RenderWindow* window = nullptr) = 0; // Keep as pure virtual

protected:
    std::stack<State*>* state_stack;
    sf::RenderWindow* window;
};
#endif // STATE_HPP
