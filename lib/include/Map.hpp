#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <Item.hpp>

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
    int RandomItemIndex(const std::vector<Item>& items) const;
    Item GetRandomItem();
    void InitInventory();
    void SetItemCollected(bool itemCollected_);
    void SetItemIntersected(bool itemIntersected_);
    bool itemCollected = false; 
    bool itemIntersected = false;

private:
    sf::RectangleShape wall_;
    std::map <std::string, sf::Texture> texture_map;
    std::vector <Item> items;
    sf::Text message;
    sf::Font font;
    int cellWidth;
    int cellHeight;
    int mapWidth;
    int mapHeight;
    int currentLevel;
    int randomItemIndex;
    int CalculateRoomCount() const;
    int CountFilledNeighbors(int x, int y) const;
    std::pair<int, int> FindFarthestRoom(int startX, int startY) const;
};

#endif
