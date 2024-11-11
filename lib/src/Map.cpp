#include "Map.hpp"
#include <random>
#include <queue>
#include <iostream>
#include <cmath>

Map::Map(int width, int height, int level)
    : mapWidth(width), mapHeight(height), cellWidth(150), cellHeight(150), currentLevel(level) {
    floorplan.resize(mapHeight / cellHeight, std::vector<CellType>(mapWidth / cellWidth, EMPTY));

    LoadTextures();
    GenerateMap();
}

const sf::FloatRect Map::GetBounds() const {
    return sf::FloatRect(0, 0, mapWidth, mapHeight);
}

CellType Map::GetCellType(int x, int y) const {
    if (x < 0 || x >= mapWidth / cellWidth || y < 0 || y >= mapHeight / cellHeight) {
        return EMPTY;
    }
    return floorplan[y][x]; 
}

int Map::GetCellWidth() const {
    return cellWidth;
}

int Map::GetCellHeight() const {
    return cellHeight;
}

int Map::CalculateRoomCount() const {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> randomRoomCount(0, 2); 

    int baseRooms = currentLevel == 1 ? 7 : 5 + (currentLevel-1); 
    return randomRoomCount(rng) + baseRooms + static_cast<int>((currentLevel - 1) * 2.6);
}

int Map::CountFilledNeighbors(int x, int y) const {
    int filledNeighbors = 0;
    std::vector<std::pair<int, int>> directions = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}
    };
    
    for (const auto& dir : directions) {
        int checkX = x + dir.first;
        int checkY = y + dir.second;
        if (checkX >= 0 && checkX < (mapWidth / cellWidth) &&
            checkY >= 0 && checkY < (mapHeight / cellHeight) &&
            floorplan[checkY][checkX] != EMPTY) {
            filledNeighbors++;
        }
    }
    return filledNeighbors;
}

std::pair<int, int> Map::FindFarthestRoom(int startX, int startY) const {
    std::pair<int, int> farthestRoom = {-1, -1};
    double maxDistance = -1.0;

    for (int y = 0; y < floorplan.size(); ++y) {
        for (int x = 0; x < floorplan[y].size(); ++x) {
            if (floorplan[y][x] == FLOOR && CountFilledNeighbors(x, y) == 1) {
                double distance = std::sqrt(std::pow(x - startX, 2) + std::pow(y - startY, 2));
                if (distance > maxDistance) {
                    maxDistance = distance;
                    farthestRoom = {x, y};
                }
            }
        }
    }
    return farthestRoom;
}

void Map::GenerateMap() {
    const int maxRooms = CalculateRoomCount(); 
    std::queue<std::pair<int, int>> cellQueue;
    int roomCount = 0;
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> distX(0, (mapWidth / cellWidth) - 1);
    std::uniform_int_distribution<int> distY(0, (mapHeight / cellHeight) - 1);
    std::uniform_real_distribution<float> randomChance(0.0f, 1.0f);

    int startX = (mapWidth / cellWidth) / 2;
    int startY = (mapHeight / cellHeight) / 2;
    floorplan[startY][startX] = FLOOR;
    cellQueue.push({startX, startY});
    roomCount++;

    std::vector<std::pair<int, int>> directions = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}
    };

    while (!cellQueue.empty() && roomCount < maxRooms) {
        auto currentCell = cellQueue.front();
        cellQueue.pop();

        for (const auto& direction : directions) {
            int neighborX = currentCell.first + direction.first;
            int neighborY = currentCell.second + direction.second;

            if (neighborX < 0 || neighborX >= (mapWidth / cellWidth) || 
                neighborY < 0 || neighborY >= (mapHeight / cellHeight)) {
                continue;
            }

            if (floorplan[neighborY][neighborX] != EMPTY) {
                continue;
            }

            int filledNeighbors = CountFilledNeighbors(neighborX, neighborY);
            if (filledNeighbors > 1 || roomCount >= maxRooms || randomChance(rng) < 0.5f) {
                continue;
            }

            floorplan[neighborY][neighborX] = FLOOR;
            cellQueue.push({neighborX, neighborY});
            roomCount++;
        }
    }

    auto placeSpecialRoom = [&](CellType type) {
        while (true) {
            int randX = distX(rng);
            int randY = distY(rng);
            if (floorplan[randY][randX] == FLOOR) {
                floorplan[randY][randX] = type;
                break;
            }
        }
    };

    placeSpecialRoom(REWARD);
    placeSpecialRoom(SECRET);

    auto farthestRoom = FindFarthestRoom(startX, startY);
    if (farthestRoom.first != -1) {
        floorplan[farthestRoom.second][farthestRoom.first] = BOSS;
    }
}

void Map::LoadTextures() {
    if (!texture_map["room"].loadFromFile(".\\resources\\floor.png")) {
        std::cerr << "Error loading normal room texture" << std::endl;
    }
    if (!texture_map["boss"].loadFromFile(".\\resources\\boss_room.png")) {
        std::cerr << "Error loading boss room texture" << std::endl;
    }
    if (!texture_map["treasure"].loadFromFile(".\\resources\\reward.png")) {
        std::cerr << "Error loading treasure room texture" << std::endl;
    }
    if (!texture_map["secret"].loadFromFile(".\\resources\\secret_room.png")) {
        std::cerr << "Error loading secret room texture" << std::endl;
    }
    if (!texture_map["Mouse"].loadFromFile(".\\resources\\mouse.png")) 
    {
        throw "Error al cargar la textura";
    }
}

void Map::DrawRoom(sf::RenderWindow* window, int roomX, int roomY) {
    sf::RectangleShape rect(sf::Vector2f(cellWidth, cellHeight));
    rect.setPosition(roomX * cellWidth, roomY * cellHeight);

    Item mouse = Item("mouse", sf::Sprite(texture_map["Mouse"]));
    switch (floorplan[roomY][roomX]) {
        case EMPTY:
            rect.setFillColor(sf::Color::Black);
            rect.setTexture(nullptr);
            break;
        case FLOOR:
            rect.setTexture(&texture_map["room"]);
            window->draw(rect);
            break;
        case BOSS:
            rect.setTexture(&texture_map["boss"]);
            window->draw(rect);
            break;
        case REWARD:
            rect.setTexture(&texture_map["treasure"]);
            mouse.setPosition(sf::Vector2f(
                rect.getPosition().x + (rect.getGlobalBounds().width / 2.f) - (mouse.GetGlobalBounds().width / 4.5f),
                rect.getPosition().y + (rect.getGlobalBounds().height / 2.f) - (mouse.GetGlobalBounds().height / 4.5f)
                ));
            mouse.setScale(sf::Vector2f(0.4f, 0.4f));
            window->draw(rect);
            mouse.Draw(*window);          
            break;
        case SECRET:
            rect.setTexture(&texture_map["secret"]);
            window->draw(rect);
            break;
    }
}

void Map::Draw(sf::RenderWindow* window) {
    for (int y = 0; y < floorplan.size(); ++y) {
        for (int x = 0; x < floorplan[y].size(); ++x) {
            sf::RectangleShape rect(sf::Vector2f(cellWidth, cellHeight));
            rect.setPosition(x * cellWidth, y * cellHeight);

            switch (floorplan[y][x]) {
                case EMPTY:
                rect.setFillColor(sf::Color::Black);
                rect.setTexture(nullptr);
                break;
                case FLOOR:
                    rect.setTexture(&texture_map["room"]);
                    break;
                case BOSS:
                    rect.setTexture(&texture_map["boss"]);
                    break;
                case REWARD:
                    rect.setTexture(&texture_map["treasure"]);
                    break;
                case SECRET:
                    rect.setTexture(&texture_map["secret"]);
                    break;
            }

            window->draw(rect);
        }
    }
}
