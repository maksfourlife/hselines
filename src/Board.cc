#include <iostream>
#include "Board.hh"

std::map<BallType, std::string> ballName = {
    {BallType::Baren, "baren"},
    {BallType::Ice, "ice"},
    {BallType::Lava, "lava"},
    {BallType::Terran, "terran"}};

Board::Board(sf::Vector2f pos, sf::Vector2u size, size_t initialBalls)
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

    this->generateBalls(initialBalls);
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
                // todo: animate
                std::cout << this->generateBalls(3) << std::endl;
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
    if (this->ballGrid[dst] != BallType::None)
        return false;
    this->ballGrid[dst] = this->ballGrid[src];
    this->ballGrid.erase(src);
    return true;
}

// if generated tail is not empty, iterate eevery possible
bool Board::generateBalls(size_t numBalls)
{
    size_t flat = this->size.x * this->size.y;
    for (size_t i = 0; i < numBalls; i++)
    {
        auto r = std::rand();
        size_t tile = r % flat;
        auto ballType = (BallType)(r % _NUM_BALL_TYPES);
        bool ok = false;
        for (auto j = 0; j < flat; j++)
        {
            auto _tile = (tile + j) % flat;
            if (this->ballGrid[_tile] == BallType::None)
            {
                this->ballGrid[_tile] = ballType;
                ok = true;
                break;
            }
        }
        if (!ok)
            return false;
    }

    return true;
}
