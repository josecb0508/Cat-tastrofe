#include "State.hpp"

State::State(std::stack<State*> *state_stack, sf::RenderWindow* window)
{
    this->window = window;
    this->state_stack = state_stack;
}