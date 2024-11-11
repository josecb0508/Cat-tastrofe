#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>
#include <stack>
#include "Cat.hpp"
#include "Golem.hpp"
#include "Level.hpp"
#include "InventoryState.hpp"

class GameState : public State
{
public:
    GameState(std::stack<State*>* state_stack, sf::RenderWindow* window);
    ~GameState();

    void Init() override; 
    void ProcessInput(sf::Event& event) override; 
    void Update(const float& deltaTime) override; 
    void Draw(sf::RenderWindow* window = nullptr) override; 
    void LoadTextures();

private:
    int current_level;        
    Cat cat;                  
    Golem golem;             
    Map room;
    sf::Texture room_texture_;
    sf::Texture treasureroom_Texture_;
    sf::Texture bossroom_Texture_;
    sf::Texture secretroom_texture_;          
    //Level level;            

    
    void DrawMinimap(sf::RenderWindow* window);
};

#endif
