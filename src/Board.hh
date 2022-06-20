#pragma once
#include "gameobject.hh"
#include "ResourceManager.hh"
#include <SFML/Graphics.hpp>

class Board : GameObject
{
public:
    Board(const ResourceManager &assets);

private:
    sf::Sprite *tileSprite;
};
