#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void handleEvent(const sf::Event &ev) = 0;
};
