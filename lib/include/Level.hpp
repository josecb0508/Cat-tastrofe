#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "Map.hpp"
#include <SFML/Graphics.hpp>

class Level : public Map {
public:
    Level(Map* map, int level);  
    void DrawCurrentRoom(sf::RenderWindow* window);
    void SetCurrentRoom(int x, int y);  
    void MoveToRoom(int dx, int dy);      

private:
    Map* map_;  
    int currentRoomX;
    int currentRoomY;
    sf::Texture floorTexture_;
    sf::Texture bossTexture_;
    sf::Texture rewardTexture_;
    sf::Texture secretTexture_;
    sf::Texture defaultTexture_;

    
    int cellWidth_;  
    int cellHeight_; 

    void LoadRoomTextures();
    void DrawRoom(int x, int y, sf::RenderWindow* window);
};

#endif
