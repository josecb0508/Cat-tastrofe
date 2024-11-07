#ifndef TILES_HPP
#define TILES_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Map.hpp" 

class Tiles {
public:
    Tiles(Map* map, float scale = 1.0f);  
    void LoadTextures();
    void GenerateTileMatrices();
    void Draw(sf::RenderWindow* window);

private:
    Map* map_;
    std::vector<std::vector<sf::Sprite>> roomTileMatrices;

    sf::Texture normalRoomTexture_;
    sf::Texture treasureRoomTexture_;
    sf::Texture bossRoomTexture_;
    sf::Texture secretRoomTexture_;
    sf::Texture emptyTexture_;

    float scale_;  

    void GenerateRoomTileMatrix(int startX, int startY, int roomWidth, int roomHeight, CellType roomType);
};

#endif
