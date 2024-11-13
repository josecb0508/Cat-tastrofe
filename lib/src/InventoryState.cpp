#include <inventoryState.hpp>

InventoryState::InventoryState(std::stack<State*> *state_stack, sf::RenderWindow* window, Cat* cat)
    : State(state_stack, window)
{
    items = cat->GetInventory();
    Init();
}

InventoryState::~InventoryState() {}

void InventoryState::Init()
{
    font.loadFromFile(".\\resources\\Silkscreen-Regular.ttf");

    title.setFont(font);
    title.setFillColor(Color::Black);
    title.setOutlineColor(Color::White);
    title.setOutlineThickness(2);
    title.setString("INVENTARIO");
    title.setCharacterSize(60);
    title.setPosition(Vector2f((800 - title.getGlobalBounds().width) / 2,75));

    for (size_t i = 0; i < items.size(); ++i)
    {
        name.setFont(font);
        name.setFillColor(sf::Color::White);
        name.setString(items[i].GetName());
        name.setCharacterSize(20);
        name.setPosition(Vector2f(200, 100 + (i * 50)));
        names.push_back(name);

        sf::Sprite icon = items[i].GetIcon();
        icon.setScale(sf::Vector2f(0.4f, 0.4f));
        icon.setPosition(Vector2f(100, 100 + (i * 50)));
        icons.push_back(icon);
    } 
}

void InventoryState::ProcessInput(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::I) 
        {
            state_stack->pop();
        }
    }
}

void InventoryState::Update(const float& deltaTime)
{
}

void InventoryState::Draw(sf::RenderWindow* _window)
{
    if (!_window)
    {
        _window = window;
    }

    for (size_t i = 0; i < items.size(); ++i)
    {
        _window->draw(icons[i]);
        _window->draw(names[i]);
    }   
}