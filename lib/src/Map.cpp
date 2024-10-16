#include "Map.hpp"
#include <random>
#include <queue>
#include <iostream>

Map::Map(int width, int height)
    : mapWidth(width), mapHeight(height), cellWidth(100), cellHeight(100) {
    floorplan.resize(mapHeight / cellHeight, std::vector<CellType>(mapWidth / cellWidth, EMPTY));
     GenerateMap();
}
 
const sf::FloatRect Map::GetBounds() const {
    return sf::FloatRect(0, 0, mapWidth, mapHeight);
}

void Map::GenerateMap() {
    const int maxRooms = 20;  // Número máximo de habitaciones
    std::queue<std::pair<int, int>> cellQueue;
    int roomCount = 0;
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> distX(0, (mapWidth / cellWidth) - 1);
    std::uniform_int_distribution<int> distY(0, (mapHeight / cellHeight) - 1);
    std::uniform_real_distribution<float> randomChance(0.0f, 1.0f);

    // Generar la habitación inicial en el centro
    int startX = (mapWidth / cellWidth) / 2;
    int startY = (mapHeight / cellHeight) / 2;
    floorplan[startY][startX] = FLOOR;
    cellQueue.push({startX, startY});
    roomCount++;

    // Definir las direcciones
    std::vector<std::pair<int, int>> directions = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}
    };

    // Explorar las habitaciones vecinas
    while (!cellQueue.empty() && roomCount < maxRooms) {
        auto currentCell = cellQueue.front();
        cellQueue.pop();

        for (const auto& direction : directions) {
            int neighborX = currentCell.first + direction.first;
            int neighborY = currentCell.second + direction.second;

            // Verificar si la celda vecina está dentro de los límites
            if (neighborX < 0 || neighborX >= (mapWidth / cellWidth) || 
                neighborY < 0 || neighborY >= (mapHeight / cellHeight)) {
                continue;
            }

            // Comprobar si la celda vecina ya está ocupada
            if (floorplan[neighborY][neighborX] != EMPTY) {
                continue;
            }

            // Contar los vecinos ocupados
            int filledNeighbors = 0;
            for (const auto& dir : directions) {
                int checkX = neighborX + dir.first;
                int checkY = neighborY + dir.second;
                if (checkX >= 0 && checkX < (mapWidth / cellWidth) &&
                    checkY >= 0 && checkY < (mapHeight / cellHeight) &&
                    floorplan[checkY][checkX] != EMPTY) {
                    filledNeighbors++;
                }
            }

            // Si tiene más de un vecino ocupado o si se genera un número suficiente de habitaciones
            if (filledNeighbors > 1 || roomCount >= maxRooms || randomChance(rng) < 0.5f) {
                continue;
            }

            // Marcar la celda vecina como FLOOR y agregarla a la cola
            floorplan[neighborY][neighborX] = FLOOR;
            cellQueue.push({neighborX, neighborY});
            roomCount++;
        }
    }

    // Colocar habitaciones especiales
    int specialRoomCount = 0;
    while (specialRoomCount < 3) {  // Ejemplo para 3 habitaciones especiales
        int randX = distX(rng);
        int randY = distY(rng);

        if (floorplan[randY][randX] == FLOOR) {
            // Colocar una habitación especial aleatoria
            std::uniform_int_distribution<int> specialDist(1, 3); // 1: BOSS, 2: REWARD, 3: SECRET
            int specialType = specialDist(rng);
            switch (specialType) {
                case 1: 
                    floorplan[randY][randX] = BOSS; 
                    break;
                case 2: 
                    floorplan[randY][randX] = REWARD; 
                    break;
                case 3: 
                    floorplan[randY][randX] = SECRET; 
                    break;
            }
            specialRoomCount++;
        }
    }
}

void Map::Draw(sf::RenderWindow &window) {
    for (int y = 0; y < floorplan.size(); ++y) {
        for (int x = 0; x < floorplan[y].size(); ++x) {
            sf::RectangleShape rect(sf::Vector2f(cellWidth, cellHeight));
            rect.setPosition(x * cellWidth, y * cellHeight);

            switch (floorplan[y][x]) {
                case EMPTY:
                    rect.setFillColor(sf::Color::Green);
                    break;
                case FLOOR:
                    rect.setFillColor(sf::Color::White);
                    break;
                case BOSS:
                    rect.setFillColor(sf::Color::Red);
                    break;
                case REWARD:
                    rect.setFillColor(sf::Color::Yellow);
                    break;
                case SECRET:
                    rect.setFillColor(sf::Color::Blue);
                    break;
            }

            window.draw(rect);
        }
    }
} 
