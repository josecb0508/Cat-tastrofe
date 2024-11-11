#include <Item.hpp>

Item::Item(const std::string& name_, sf::Sprite icon_)
    : name(name_),icon(icon_)
{

}

void Item::SetName(const std::string& newName)
{
    name = newName;
}

std::string Item::GetName()
{
    return name;
}

void Item::SetIcon(const sf::Sprite newIcon)
{
    icon = newIcon;
}

sf::Sprite Item::GetIcon()
{
    return icon;
}

void Item::setPosition(const sf::Vector2f& position)
{
    icon.setPosition(position);
}

void Item::Draw(sf::RenderWindow& window)
{
    window.draw(icon);
}

sf::FloatRect Item::GetGlobalBounds()
{
    return icon.getGlobalBounds();
}

void Item::setScale(sf::Vector2f scale)
{
    icon.setScale(scale);
}