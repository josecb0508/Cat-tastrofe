/*#include "Tiles.hpp"
#include "Map.hpp"
#include <iostream>

Tiles::Tiles(Map* map, float scale)
    : map_(map), scale_(scale) {
    if (!normalRoomTexture_.loadFromFile("resources/normal_room.png")) {
        std::cerr << "Error loading normal room texture!" << std::endl;
    }
    if (!treasureRoomTexture_.loadFromFile("resources/treasure_room.png")) {
        std::cerr << "Error loading treasure room texture!" << std::endl;
    }
    if (!bossRoomTexture_.loadFromFile("resources/boss_room.png")) {
        std::cerr << "Error loading boss room texture!" << std::endl;
    }
    if (!secretRoomTexture_.loadFromFile("resources/secret_room.png")) {
        std::cerr << "Error loading secret room texture!" << std::endl;
    }
    if (!emptyTexture_.loadFromFile("resources/normal_room.png")) {
        std::cerr << "Error loading empty room texture!" << std::endl;
    }
}

void Tiles::GenerateRoomTileMatrix(int startX, int startY, int roomWidth, int roomHeight, CellType roomType) {
    std::vector<sf::Sprite> roomTileRow;

    for (int y = 0; y < roomHeight; ++y) {
        roomTileRow.clear();

        for (int x = 0; x < roomWidth; ++x) {
            sf::Sprite tile;
            
            CellType cellType = map_->GetCellType(startX + x, startY + y);
            
            switch (cellType) {
                case FLOOR:
                    tile.setTexture(normalRoomTexture_);
                    break;
                case BOSS:
                    tile.setTexture(bossRoomTexture_);
                    break;
                case REWARD:
                    tile.setTexture(treasureRoomTexture_);
                    break;
                case SECRET:
                    tile.setTexture(secretRoomTexture_);
                    break;
                default:
                    tile.setTexture(emptyTexture_);
                    break;
            }

            tile.setPosition(startX + x * 16 * scale_, startY + y * 16 * scale_);
            tile.setScale(scale_, scale_);

            roomTileRow.push_back(tile);
        }
        
        roomTileMatrices.push_back(roomTileRow);
    }
}

void Tiles::GenerateTileMatrices() {
    roomTileMatrices.clear(); 

    for (int y = 0; y < map_->GetBounds().height / map_->GetCellHeight(); ++y) {
        for (int x = 0; x < map_->GetBounds().width / map_->GetCellWidth(); ++x) {
            CellType cellType = map_->GetCellType(x, y);

            if (cellType == FLOOR || cellType == BOSS || cellType == REWARD || cellType == SECRET) {
                GenerateRoomTileMatrix(x * map_->GetCellWidth(), y * map_->GetCellHeight(), map_->GetCellWidth(), map_->GetCellHeight(), cellType);
            }
        }
    }
}

void Tiles::Draw(sf::RenderWindow* window) {
    for (auto& row : roomTileMatrices) {
        for (auto& tile : row) {
            window->draw(tile);
        }
    }
}
*/