#include "GameState.hpp"
#include "MenuPauseState.hpp"
#include "Golem.hpp"
#include "Tiles.hpp"
#include <iostream>

GameState::GameState(std::stack<State*>* state_stack, sf::RenderWindow* window)
    : State(state_stack, window),
      current_level(1), 
      room(800, 600, current_level),  
      cat(".\\resources\\cat.png", sf::Vector2f(0,0)),
      golem(".\\resources\\enemy.png", ".\\resources\\enemy.png", sf::Vector2f(380, 350))
      //level(&room, current_level)  
{
    LoadTextures();
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
    if (event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::P) 
        {
            state_stack->push(new MenuPauseState(state_stack, window));
        }
    }
    if (event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::I) 
        {
            state_stack->push(new InventoryState(state_stack, window, &cat));
        }
    }
}

void GameState::Update(const float& deltaTime)
{
    cat.Move(deltaTime, room, golem);
    golem.Move(deltaTime, cat.GetPosition());

    if(cat.GetHealth() <= 0)
    {
        state_stack->push(new GameOverState(state_stack, window));
    }
}

void GameState::LoadTextures() {
    if (!room_texture_.loadFromFile(".\\resources\\normal_room.png")) {
        std::cerr << "Error loading normal room texture" << std::endl;
    }
    if (!bossroom_Texture_.loadFromFile(".\\resources\\boss_room.png")) {
        std::cerr << "Error loading boss room texture" << std::endl;
    }
    if (!treasureroom_Texture_.loadFromFile(".\\resources\\treasure_room.png")) {
        std::cerr << "Error loading treasure room texture" << std::endl;
    }
    if (!secretroom_texture_.loadFromFile(".\\resources\\secret_room.png")) {
        std::cerr << "Error loading secret room texture" << std::endl;
    }
}

void GameState::DrawMinimap(sf::RenderWindow* window)
{
    const float minimapWidth = 100.f;  
    const float minimapHeight = 75.f;  
    
    const float scaleX = minimapWidth / room.GetMapWidth();  
    const float scaleY = minimapHeight / room.GetMapHeight(); 
    
    sf::Vector2u windowSize = window->getSize();
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);

    float minimapPosX = windowWidth - minimapWidth - 10.f;
    float minimapPosY = 10.f;

    sf::RectangleShape minimap(sf::Vector2f(minimapWidth, minimapHeight));
    minimap.setFillColor(sf::Color(50, 50, 50, 180)); 
    minimap.setPosition(minimapPosX, minimapPosY);  

    window->draw(minimap);

    for (std::size_t y = 0; y < room.floorplan.size(); ++y) {
        for (std::size_t x = 0; x < room.floorplan[y].size(); ++x) {
            sf::RectangleShape cell(sf::Vector2f(room.GetCellWidth() * scaleX, room.GetCellHeight() * scaleY));
            cell.setPosition(minimapPosX + x * room.GetCellWidth() * scaleX + 1.f, minimapPosY + y * room.GetCellHeight() * scaleY + 1.f);

            switch (room.floorplan[y][x]) {
                case EMPTY:
                    cell.setFillColor(sf::Color::Black);
                    cell.setTexture(nullptr);
                    break;
                case FLOOR:
                    cell.setTexture(&room_texture_);
                    break;
                case BOSS:
                    cell.setTexture(&bossroom_Texture_);
                    break;
                case REWARD:
                    cell.setTexture(&treasureroom_Texture_);
                    break;
                case SECRET:
                    cell.setTexture(&secretroom_texture_);
                    break;
            }

            window->draw(cell);
        }
    }

    sf::CircleShape playerMarker(2.f); 
    playerMarker.setFillColor(sf::Color::Red);

    float playerMinimapX = cat.GetPosition().x * scaleX;
    float playerMinimapY = cat.GetPosition().y * scaleY;

    playerMarker.setPosition(minimapPosX + playerMinimapX, minimapPosY + playerMinimapY);
    
    window->draw(playerMarker);
}


void GameState::Draw(sf::RenderWindow* window)
{
    sf::Vector2f playerPos = cat.GetPosition();

    int playerX = static_cast<int>(playerPos.x) / room.GetCellWidth();
    int playerY = static_cast<int>(playerPos.y) / room.GetCellHeight();

    room.DrawRoom(window, playerX, playerY);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
        DrawMinimap(window);
    }

    if (!golem.IsDead()) {
        golem.Draw(*window);
    }
    cat.Draw(*window);
}