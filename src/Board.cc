#include <iostream>
#include "Board.hh"

std::map<BallType, std::string> ballName = {
    {BallType::Baren, "baren"},
    {BallType::Ice, "ice"},
    {BallType::Lava, "lava"},
    {BallType::Terran, "terran"}};

Board::Board(sf::Vector2f pos, sf::Vector2u size)
{
    this->pos = pos;
    this->size = size;

    auto resManager = ResourceManager::getInstance();

    auto texture = (sf::Texture *)resManager.get("textures/tile");
    this->tileSize = texture->getSize();
    this->tileSprite = sf::Sprite(*texture);

    this->selectionSprite = sf::Sprite(
        *(sf::Texture *)resManager.get("textures/selection"));

    for (auto &item : ballName)
    {
        auto textureName = "textures/" + item.second;
        sf::Sprite s(*(sf::Texture *)resManager.get(textureName));
        this->ballSprites.insert({item.first, s});
    }
}

void Board::draw(sf::RenderWindow &window)
{
    size_t flat = this->size.x * this->size.y;
    for (size_t i = 0; i < flat; i++)
    {
        auto pos = sf::Vector2f(
            this->pos.x + this->tileSize.x * (i % this->size.x),
            this->pos.y + this->tileSize.y * (i / this->size.x));
        this->tileSprite.setPosition(pos);
        window.draw(this->tileSprite);
    }
}