#ifndef STATE_HPP
#define STATE_HPP
#include <SFML/Graphics.hpp>
#include <stack>
#include <map>

class State
{
public:
    State(std::stack<State*> *state_stack, sf::RenderWindow* window);
    virtual ~State(){}; 

    virtual void Init() = 0; 
    virtual void ProcessInput(sf::Event& event) = 0; 
    virtual void Update(const float& deltaTime) = 0; 
    virtual void Draw(sf::RenderWindow* window = nullptr) = 0; 

protected:
    std::stack<State*>* state_stack;
    sf::RenderWindow* window;
};
#endif 
