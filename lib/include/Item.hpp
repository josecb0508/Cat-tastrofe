#include <SFML/Graphics.hpp>

class Item {
public:
    Item(const std::string& name, sf::Sprite icon);
    void SetName(const std::string& newName);
    std::string GetName();
    void SetIcon(const sf::Sprite newIcon);
    sf::Sprite GetIcon();
    void setPosition(const sf::Vector2f& position);
    void Draw(sf::RenderWindow& window);
    sf::FloatRect GetGlobalBounds();
    void setScale(sf::Vector2f scale);

private:
    std::string name;
    sf::Sprite icon;
};
