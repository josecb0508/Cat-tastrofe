#include <SFML/Graphics.hpp>
#include "Game.hpp"

Game::Game() 
{
    this->InitGame();
}

Game::~Game()
{
    delete this->window;
    while (!this->state_stack.empty())
    {
        delete this->state_stack.top();
        this->state_stack.pop();
    }
}

void Game::InitGame()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1000, 700), "Cat-tastrofe");
    this->state_stack.push(new Menu(&state_stack, window, 1200, 700));
    window->setFramerateLimit(60);
}

void Game::run() {
    while (window->isOpen()) 
    {
        deltaTime = clock.restart().asSeconds();  
        HandleEvents(); 
        Update();     
        Draw();          
    }
}

void Game::HandleEvents() {
    sf::Event event;
    while (window->pollEvent(event)) 
    {
        if (event.type == sf::Event::Closed) 
        {
            window->close();
        }
        if (event.type == sf::Event::KeyPressed) 
        {
            if (!this->state_stack.empty())
            {
                this->state_stack.top()->ProcessInput(event);
            }
        }
    }
}

void Game::Update() 
{
    if (!this->state_stack.empty())
    {
        this->state_stack.top()->Update(deltaTime);  
    }
}

void Game::Draw()
{
    this->window->clear(); 

    if (!this->state_stack.empty())
    {
        this->state_stack.top()->Draw(window);  
    }

    this->window->display(); 
}