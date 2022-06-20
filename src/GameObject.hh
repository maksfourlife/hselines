#pragma once

#include <SFML/Window.hpp>

class GameObject
{
public:
    virtual void draw(const sf::Window &window) = const 0;
};
