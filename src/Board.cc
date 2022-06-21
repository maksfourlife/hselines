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
        this->ballSprites[item.first] = s;
    }

    // todo: remove
    this->ballGrid[10] = BallType::Lava;
    this->ballGrid[5] = BallType::Ice;
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

        if (this->selectedTile == i)
        {
            this->selectionSprite.setPosition(pos);
            window.draw(this->selectionSprite);
        }

        auto ballType = this->ballGrid[i];
        if (ballType != BallType::None)
        {
            auto sprite = this->ballSprites[ballType];
            sprite.setPosition(pos);
            window.draw(sprite);
        }
    }
}

void Board::handleEvent(const sf::Event &ev)
{
    static int mouseX, mouseY;
    if (ev.type == sf::Event::MouseMoved)
    {
        mouseX = ev.mouseMove.x;
        mouseY = ev.mouseMove.y;
    }
    else if (ev.type == sf::Event::MouseButtonReleased)
    {
        size_t clickedTile;
        if (getClickedTile(mouseX, mouseY, clickedTile))
        {
            if (this->selectedTile == -1 && this->ballGrid[clickedTile] != BallType::None)
                this->selectedTile = clickedTile;
            else if (this->selectedTile != -1 && this->moveBall(selectedTile, clickedTile))
            {
                this->selectedTile = -1;
                // animate
            }
        }
    }
}

bool Board::getClickedTile(int mouseX, int mouseY, size_t &clickedTile)
{
    auto x = (mouseX - (int)this->pos.x) / this->tileSize.x;
    auto y = (mouseY - (int)this->pos.y) / this->tileSize.y;
    clickedTile = x + y * this->size.x;
    return true;
}

bool Board::moveBall(size_t src, size_t dst)
{
    std::cout << "move from: " << src << " to: " << dst << std::endl;
    if (this->ballGrid[dst] != BallType::None)
        return false;
    this->ballGrid[dst] = this->ballGrid[src];
    this->ballGrid.erase(src);
    return true;
}
