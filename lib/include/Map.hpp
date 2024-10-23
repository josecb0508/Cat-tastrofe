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
    void Draw(sf::RenderWindow &window);
    const sf::FloatRect GetBounds() const;

private:
    sf::RectangleShape wall_;
    sf::Texture room_texture_;
    sf::Texture treasureroom_Texture_;
    sf::Texture bossroom_Texture_;
    sf::Texture secretroom_texture_;
    std::vector<std::vector<CellType>> floorplan;
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