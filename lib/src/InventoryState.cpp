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
    title.setFillColor(Color::White);
    title.setOutlineThickness(2);
    title.setString("INVENTORY");
    title.setCharacterSize(60);
    title.setPosition(Vector2f((1000 - title.getGlobalBounds().width) / 2, 50));
    
    float iconStartY = (title.getPosition().y + title.getGlobalBounds().height) + 20;
    float centerX = 500;

    for (size_t i = 0; i < items.size(); ++i)
    {
        sf::Sprite icon = items[i].GetIcon();
        icon.setScale(sf::Vector2f(0.3f, 0.3f));
        float iconX = centerX - (icon.getGlobalBounds().width + 10);
        icon.setPosition(Vector2f(iconX, iconStartY + (i * 50)));
        icons.push_back(icon);

        name.setFont(font);
        name.setFillColor(sf::Color::White);
        name.setString(items[i].GetName());
        name.setCharacterSize(20);
        float nameX = (icon.getPosition().x + icon.getGlobalBounds().width) + 10;
        name.setPosition(sf::Vector2f(nameX, icon.getPosition().y + 20));
        names.push_back(name);
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

    _window->draw(title);
    for (size_t i = 0; i < items.size(); ++i)
    {
        _window->draw(icons[i]);
        _window->draw(names[i]);
    }   
}