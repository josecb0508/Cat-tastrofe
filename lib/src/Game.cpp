#include <SFML/Graphics.hpp>
#include "Cat.hpp"
#include "Map.hpp"
#include "Enemy.hpp"
#include <Menu.hpp>
#include "Game.hpp"
#include "Golem.hpp"

Game::Game() 
    : window(sf::VideoMode(800, 600), "Cat-tastrofe"), 
      menu(800, 600), 
      current_level(1), 
      room(800, 600, current_level),
      cat("resources/cat.png", sf::Vector2f(0,0)),
      golem("resources/enemy.png", "resources/enemy.png", sf::Vector2f(380, 350)) 
{
    window.setFramerateLimit(60);
    initGame();
}
void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        window.clear();
        update();
        window.display();
    }
}

void Game::initGame() {
    sf::Vector2f initialPosition(
        room.GetBounds().width / 2 - (30 * 1.5 / 2), 
        room.GetBounds().height / 2 - (30 * 1.5 / 2)
    );

    cat.SetPosition(initialPosition);
    golem.setPosition(sf::Vector2f(200,150));
    golem.setHealth(350);

    if (!texture.loadFromFile("resources/ciudad.png")) {
        throw "Error al cargar la textura";
    }

    rect.setSize(sf::Vector2f(800, 600));
    rect.setTexture(&texture);
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            handleMenuInput(event);
        }
    }
}

void Game::handleMenuInput(const sf::Event& event) {
    if (event.key.code == sf::Keyboard::Down) {
        menu.MoveDown();
    }
    if (event.key.code == sf::Keyboard::Up) {
        menu.Moveup();
    }
    if (event.key.code == sf::Keyboard::Return) {
        int x = menu.pressed();
        if (x == 0) {
            startGameLoop();
        }
        if (x == 1) {
            window.close();
        }
    } 
}

void Game::startGameLoop() {
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        window.clear();
        cat.Move(deltaTime, room, golem);
        golem.Move(deltaTime, cat.GetPosition());
        room.Draw(window);
        if (!golem.IsDead()) {
            golem.Draw(window);
        }
        cat.Draw(window);
        window.display();
    }
}

void Game::update() {
    window.draw(rect);
    menu.draw(window);
}