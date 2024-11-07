#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <vector>

enum CellType {
    EMPTY,
    FLOOR,
    BOSS,
    REWARD,
    SECRET
};

class Map {
public:
    Map(int width, int height, int level);
    void GenerateMap();
    void LoadTextures();
    virtual void Draw(sf::RenderWindow* window);  
    void DrawRoom(sf::RenderWindow* window, int roomX, int roomY);  
    const sf::FloatRect GetBounds() const;
    CellType GetCellType(int x, int y) const;
    int GetCellWidth() const;
    int GetCellHeight() const;
    std::vector<std::vector<CellType>> floorplan;
    int GetMapWidth() const { return mapWidth; }
    int GetMapHeight() const { return mapHeight; }

private:
    sf::RectangleShape wall_;
    sf::Texture room_texture_;
    sf::Texture treasureroom_Texture_;
    sf::Texture bossroom_Texture_;
    sf::Texture secretroom_texture_;
    int cellWidth;
    int cellHeight;
    int mapWidth;
    int mapHeight;
    int currentLevel;
    int CalculateRoomCount() const;
    int CountFilledNeighbors(int x, int y) const;
    std::pair<int, int> FindFarthestRoom(int startX, int startY) const;
};

#endif
