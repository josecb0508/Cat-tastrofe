#include "GameState.hpp"
#include "Golem.hpp"

GameState::GameState(std::stack<State*>* state_stack, sf::RenderWindow* window)
    : State(state_stack, window),
      current_level(1), 
      room(800, 600, current_level), 
      cat("resources/cat.png", sf::Vector2f(0,0)),
      golem("resources/enemy.png", "resources/enemy.png", sf::Vector2f(380, 350)) 
{
    Init();
}

GameState::~GameState(){}

void GameState::Init() 
{
    sf::Vector2f initialPosition(
        room.GetBounds().width / 2 - (30 * 1.5 / 2), 
        room.GetBounds().height / 2 - (30 * 1.5 / 2)
    );

    cat.SetPosition(initialPosition);
    golem.setPosition(sf::Vector2f(200,150));
    golem.setHealth(150);
}

void GameState::ProcessInput(sf::Event& event)
{
    // Implement input handling here if needed
}

void GameState::Update(const float& deltaTime)
{
    cat.Move(deltaTime, room, golem);
    golem.Move(deltaTime, cat.GetPosition());
}

void GameState::Draw(sf::RenderWindow* window)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
    {
        room.Draw(window);
    }

    if (!golem.IsDead()) {
        golem.Draw(*window);
    }
    cat.Draw(*window);
}