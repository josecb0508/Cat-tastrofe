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
    Map(int width, int height);
    void GenerateMap();
    void Draw(sf::RenderWindow &window);
    const sf::FloatRect GetBounds() const;


private:
    sf::RectangleShape wall_;
    std::vector<std::vector<CellType>> floorplan;
    int cellWidth;
    int cellHeight;
    int mapWidth;
    int mapHeight;
};

#endif 

