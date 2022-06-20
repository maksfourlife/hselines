#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameObject.hh"
#include "Ball.hh"
#include "ResourceManager.hh"

class Board : GameObject
{
public:
    Board(
        ResourceManager &manager,
        const sf::Vector2f pos,
        const sf::Vector2u size);
    ~Board();

    virtual void draw(sf::RenderWindow &window) override;

private:
    sf::Sprite *tile;
    sf::Vector2f pos;
    sf::Vector2u size;
    std::vector<Ball *> balls;
};
