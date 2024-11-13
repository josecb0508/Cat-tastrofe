#include <State.hpp>
#include <Cat.hpp>

class InventoryState : public State
{
    public:
    InventoryState(std::stack<State*> *state_stack, sf::RenderWindow* window, Cat* cat);
    void Init();
    void ProcessInput(sf::Event& event); 
    void Update(const float& deltaTime); 
    void Draw(sf::RenderWindow* window);
    std::vector <sf::Sprite> icons;
    std::vector <sf::Text> names;
    ~InventoryState();

    private:
    std::vector <Item> items;
    sf::Text name;
    sf::Text title;
    Font font; 
};
