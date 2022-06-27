#include "Count.hh"
#include "ResourceManager.hh"

Count::Count(sf::Vector2f pos)
{
    this->text.setPosition(pos);
    this->text.setFont(
        *(sf::Font *)ResourceManager::getInstance()
             .get("fonts/PressStart"));
    this->text.setString(std::to_string(this->count));
}

void Count::draw(sf::RenderWindow &window)
{
    window.draw(this->text);
}

void Count::addCount(int count)
{
    this->count += count;
    this->text.setString(std::to_string(this->count));
}
