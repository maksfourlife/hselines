#pragma once
#include <SFML/Graphics.hpp>

class Count
{
public:
    Count(sf::Vector2f pos);
    void addCount(int count);

    void draw(sf::RenderWindow &window);

private:
    sf::Text text;
    int count = 0;
};
