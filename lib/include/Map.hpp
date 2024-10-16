#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>

class Map {
public:
    Map(float width, float height);
    void draw(sf::RenderWindow& window);
    const sf::FloatRect getBounds() const;

private:
    sf::RectangleShape wall_;
};

#endif 


/*#ifndef MAP_HPP
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
    void generateMap();
    void draw(sf::RenderWindow &window);

private:
    std::vector<std::vector<CellType>> floorplan;
    int cellWidth;
    int cellHeight;
    int mapWidth;
    int mapHeight;
};

#endif // MAP_HPP*/

