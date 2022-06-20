#include "Board.hh"
#include <iostream>

#define TILE_SIZE 58

Board::Board(
    ResourceManager &manager,
    const sf::Vector2f pos,
    const sf::Vector2u size)
{
    this->pos = pos;
    this->size = size;

    this->tile = new sf::Sprite(
        *(sf::Texture *)manager.get("textures/tile"));
}

Board::~Board()
{
    delete this->tile;
}

void Board::draw(sf::RenderWindow &window)
{
    for (size_t i = 0; i < this->size.x; i++)
        for (size_t j = 0; j < this->size.y; j++)
        {
            auto pos = this->pos + sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE);
            this->tile->setPosition(pos);
            window.draw(*this->tile);
        }
}