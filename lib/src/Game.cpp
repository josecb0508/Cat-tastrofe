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
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Cat-tastrofe");
    this->state_stack.push(new Menu(&state_stack, window, 800, 600));
    window->setFramerateLimit(60);
}

void Game::run() {
    while (window->isOpen()) 
    {
        deltaTime = clock.restart().asSeconds();  // Actualiza deltaTime aquí
        HandleEvents();  // Llama a HandleEvents solo una vez
        Update();        // Actualiza el estado
        Draw();          // Dibuja el contenido en la ventana
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
        this->state_stack.top()->Update(deltaTime);  // Usa deltaTime aquí
    }
}

void Game::Draw()
{
    this->window->clear();  // Este clear debe ir aquí

    if (!this->state_stack.empty())
    {
        this->state_stack.top()->Draw(window);  // Asegúrate de pasar el window
    }

    this->window->display();  // Muestra el contenido dibujado
}