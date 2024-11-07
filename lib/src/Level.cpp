#include "Level.hpp"
#include <iostream>

Level::Level(Map* map, int level)
    : Map(map->GetMapWidth(), map->GetMapHeight(), level),  
      map_(map), 
      currentRoomX(0), currentRoomY(0) {
    LoadRoomTextures();
}

void Level::LoadRoomTextures() {
    if (!floorTexture_.loadFromFile("resources/floor.png")) {
        std::cerr << "Error cargando textura de suelo\n";
    }
    if (!bossTexture_.loadFromFile("resources/boss_room.png")) {
        std::cerr << "Error cargando textura de jefe\n";
    }
    if (!rewardTexture_.loadFromFile("resources/reward.png")) {
        std::cerr << "Error cargando textura de recompensa\n";
    }
    if (!secretTexture_.loadFromFile("resources/secret_room.png")) {
        std::cerr << "Error cargando textura de secreto\n";
    }
    if (!defaultTexture_.loadFromFile("resources/room_texture.png")) {
        std::cerr << "Error cargando textura por defecto\n";
    }
}

void Level::SetCurrentRoom(int x, int y) {
    if (x >= 0 && x < map_->GetMapWidth() / map_->GetCellWidth() && 
        y >= 0 && y < map_->GetMapHeight() / map_->GetCellHeight()) {
        currentRoomX = x;
        currentRoomY = y;
    }
}

void Level::MoveToRoom(int dx, int dy) {
    int newX = currentRoomX + dx;
    int newY = currentRoomY + dy;
    if (newX >= 0 && newX < map_->GetMapWidth() / map_->GetCellWidth() && 
        newY >= 0 && newY < map_->GetMapHeight() / map_->GetCellHeight()) {
        currentRoomX = newX;
        currentRoomY = newY;
    }
}

void Level::DrawCurrentRoom(sf::RenderWindow* window) {
    int numCellsWide = map_->GetMapWidth() / map_->GetCellWidth();   
    int numCellsTall = map_->GetMapHeight() / map_->GetCellHeight();  

    for (int y = 0; y < numCellsTall; ++y) {
        for (int x = 0; x < numCellsWide; ++x) {
            DrawRoom(x, y, window);
        }
    }
}

void Level::DrawRoom(int x, int y, sf::RenderWindow* window) {

    CellType roomType = map_->GetCellType(x, y);
    sf::RectangleShape roomShape(sf::Vector2f(400, 300)); 

    roomShape.setPosition(x * map_->GetCellWidth(), y * map_->GetCellHeight());  

    switch (roomType) {
        case FLOOR:
            roomShape.setTexture(&floorTexture_);
            break;
        case BOSS:
            roomShape.setTexture(&bossTexture_);
            break;
        case REWARD:
            roomShape.setTexture(&rewardTexture_);
            break;
        case SECRET:
            roomShape.setTexture(&secretTexture_);
            break;
        default:
            roomShape.setFillColor(sf::Color::Black);
            break;
    }

    window->draw(roomShape);
}
