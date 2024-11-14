#include "GameState.hpp"
#include "MenuPauseState.hpp"
#include "Golem.hpp"
#include "Tiles.hpp"
#include <iostream>

GameState::GameState(std::stack<State*>* state_stack, sf::RenderWindow* window)
    : State(state_stack, window),
      current_level(1), 
      room(20000, 20000, current_level),  
      cat(".\\resources\\cat.png", sf::Vector2f(0,0)),
      golem(".\\resources\\enemy.png", ".\\resources\\enemy.png", sf::Vector2f(380, 350))
{
    LoadTextures();
    Init();

    camera.setSize(room.GetCellWidth(), room.GetCellHeight()); 
    camera.setCenter(cat.GetPosition());

    levelText_.setFont(font_);
    levelText_.setCharacterSize(20);
    levelText_.setFillColor(sf::Color::White);

    UpdateLevelText();
}

GameState::~GameState(){}

void GameState::Init() 
{
    sf::Vector2f initialPosition(
        room.GetBounds().width / 2 - (30 * 1.5 / 2), 
        room.GetBounds().height / 2 - (30 * 1.5 / 2)
    );
    sf::Vector2f golemPosition(initialPosition.x + 200, initialPosition.y + 200);


    cat.SetPosition(initialPosition);
    golem.setPosition(golemPosition);
    golem.setHealth(150);
}

void GameState::ProcessInput(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Space)
        {
            ChangeLevel();
        } 
    }
    if (event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::P) 
        {
            state_stack->push(new MenuPauseState(state_stack, window));
        }
    }
    if (event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::I) 
        {
            state_stack->push(new InventoryState(state_stack, window, &cat));
        }
    }
}

void GameState::UpdateCamera() {
    sf::Vector2f playerPos = cat.GetPosition();

    int roomX = static_cast<int>(playerPos.x) / room.GetCellWidth();
    int roomY = static_cast<int>(playerPos.y) / room.GetCellHeight();

    camera.setCenter((roomX * room.GetCellWidth()) + (room.GetCellWidth() / 2.0f),
                     (roomY * room.GetCellHeight()) + (room.GetCellHeight() / 2.0f));
}

void GameState::Update(const float& deltaTime)
{
    cat.Move(deltaTime, room, golem);
    golem.Move(deltaTime, cat.GetPosition());
    UpdateCamera();

    if(cat.GetHealth() <= 0)
    {
        state_stack->push(new GameOverState(state_stack, window));
    }
}

void GameState::LoadTextures() {
    if (!textures["floor"].loadFromFile(".\\resources\\floor_texture.png")) {
        std::cerr << "Error loading normal room texture" << std::endl;
    }
    if (!textures["boss"].loadFromFile(".\\resources\\boss_room.png")) {
        std::cerr << "Error loading boss room texture" << std::endl;
    }
    if (!textures["reward"].loadFromFile(".\\resources\\reward.png")) {
        std::cerr << "Error loading treasure room texture" << std::endl;
    }
    if (!textures["secret"].loadFromFile(".\\resources\\secret_room.png")) {
        std::cerr << "Error loading secret room texture" << std::endl;
    }
    if (!font_.loadFromFile(".\\resources\\Silkscreen-Regular.ttf")) {
        std::cerr << "Error loading font for level text" << std::endl;
    }

}

void GameState::DrawMinimap(sf::RenderWindow* window)
{
    const float baseMinimapWidth = 100.f;
    const float baseMinimapHeight = 75.f;

    bool isTabPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Tab);
    float minimapScale = isTabPressed ? 2.0f : 0.5f;

    const float minimapWidth = baseMinimapWidth * minimapScale;
    const float minimapHeight = baseMinimapHeight * minimapScale;

    const float scaleX = minimapWidth / room.GetMapWidth();
    const float scaleY = minimapHeight / room.GetMapHeight();

    sf::View view = window->getView();
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    float minimapPosX = viewCenter.x + (viewSize.x / 2) - minimapWidth - 10.f;
    float minimapPosY = viewCenter.y - (viewSize.y / 2) + 10.f;

    sf::RectangleShape minimap(sf::Vector2f(minimapWidth, minimapHeight));
    minimap.setFillColor(sf::Color(50, 50, 50, 180));
    minimap.setPosition(minimapPosX, minimapPosY);

    window->draw(minimap);

    for (std::size_t y = 0; y < room.floorplan.size(); ++y) {
        for (std::size_t x = 0; x < room.floorplan[y].size(); ++x) {
            sf::RectangleShape cell(sf::Vector2f(room.GetCellWidth() * scaleX, room.GetCellHeight() * scaleY));
            cell.setPosition(minimapPosX + x * room.GetCellWidth() * scaleX, minimapPosY + y * room.GetCellHeight() * scaleY);

            switch (room.floorplan[y][x]) {
                case EMPTY:
                    cell.setFillColor(sf::Color::Black);
                    cell.setTexture(nullptr);
                    break;
                case FLOOR:
                    cell.setTexture(&textures["floor"]);
                    break;
                case BOSS:
                    cell.setTexture(&textures["boss"]);
                    break;
                case REWARD:
                    cell.setTexture(&textures["reward"]);
                    break;
                case SECRET:
                    cell.setTexture(&textures["secret"]);
                    break;
            }

            window->draw(cell);
        }
    }

    // Crear el marcador del jugador
    sf::CircleShape playerMarker(1.0f * minimapScale);  
    playerMarker.setFillColor(sf::Color::Red);

    // Calcular en qué celda está el jugador
    int playerCellX = static_cast<int>(cat.GetPosition().x) / room.GetCellWidth();
    int playerCellY = static_cast<int>(cat.GetPosition().y) / room.GetCellHeight();

    // Posicionar el marcador en el centro de la celda actual
    float playerMinimapX = minimapPosX + playerCellX * room.GetCellWidth() * scaleX + (room.GetCellWidth() * scaleX) / 2.f - playerMarker.getRadius();
    float playerMinimapY = minimapPosY + playerCellY * room.GetCellHeight() * scaleY + (room.GetCellHeight() * scaleY) / 2.f - playerMarker.getRadius();

    playerMarker.setPosition(playerMinimapX, playerMinimapY);

    window->draw(playerMarker);
}

void GameState::ChangeLevel(){

    current_level++;
    UpdateLevelText();

    room = Map(20000, 20000, current_level);

    sf::Vector2f initialPosition(
        room.GetBounds().width / 2 - (30 * 1.5 / 2), 
        room.GetBounds().height / 2 - (30 * 1.5 / 2)
    );
    sf::Vector2f golemPosition(initialPosition.x + 200, initialPosition.y + 200);

    cat.SetPosition(initialPosition);
    /*Enemy golem(".\\resources\\enemy.png", ".\\resources\\enemy.png", sf::Vector2f(380, 350));
    golem.setPosition(golemPosition);
    golem.setHealth(150);*/

    camera.setCenter(cat.GetPosition());
}

void GameState::UpdateLevelText(){

    levelText_.setString("Floor: " + std::to_string(current_level));
    levelText_.setPosition(cat.GetHealthBarPosition().x + 120, cat.GetHealthBarPosition().y - 10);

}
void GameState::Draw(sf::RenderWindow* window)
{
    window->setView(camera);
    sf::Vector2f playerPos = cat.GetPosition();

    int playerX = static_cast<int>(playerPos.x) / room.GetCellWidth();
    int playerY = static_cast<int>(playerPos.y) / room.GetCellHeight();

    room.DrawRoom(window, playerX, playerY);
    DrawMinimap(window);

    if (!golem.IsDead()) {
        golem.Draw(*window);
    }
    cat.Draw(*window);
    window->setView(window->getDefaultView());
    cat.DrawHealthBar(*window);
    window->draw(levelText_);

}