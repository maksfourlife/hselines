#include <vector>
#include "Board.hh"

std::map<BallType, std::string> ballName = {
    {::Baren, "baren"},
    {::Ice, "ice"},
    {::Lava, "lava"},
    {::Terran, "terran"}};

Board::Board(
    sf::Vector2f pos,
    sf::Vector2u size,
    std::function<void(int)> addCount,
    size_t initialBalls)
{
    this->pos = pos;
    this->size = size;
    this->addCount = addCount;

    auto resManager = ResourceManager::getInstance();

    auto texture = (sf::Texture *)resManager.get("textures/tile");
    this->tileSize = texture->getSize();
    this->tileSprite = sf::Sprite(*texture);

    texture = (sf::Texture *)resManager.get("textures/selection");
    this->selectionSize = texture->getSize();
    this->selectionSprite = sf::Sprite(
        *texture);

    for (auto &item : ballName)
    {
        texture = (sf::Texture *)resManager.get("textures/" + item.second);
        this->ballSize = texture->getSize();
        this->ballSprites[item.first] = sf::Sprite(*texture);
    }

    this->generateBalls(initialBalls);
}

Board Board::mock(
    sf::Vector2f pos,
    sf::Vector2u size,
    sf::Vector2u tileSize,
    sf::Vector2u selectionSize,
    sf::Vector2u ballSize,
    std::function<void(int)> addCount,
    size_t initialBalls)
{
    Board b;
    b.pos = pos;
    b.size = size;
    b.addCount = addCount;
    b.tileSize = tileSize;
    b.selectionSize = selectionSize;
    b.ballSize = ballSize;
    b.generateBalls(initialBalls);
    return b;
}

void Board::draw(sf::RenderWindow &window)
{
    auto ballOffset = sf::Vector2f(
        (this->tileSize.x - this->ballSize.x) / 2,
        (this->tileSize.y - this->ballSize.y) / 2);

    auto selectionOffset = sf::Vector2f(
        (this->tileSize.x - this->selectionSize.x) / 2,
        (this->tileSize.y - this->selectionSize.y) / 2);

    size_t flat = this->size.x * this->size.y;
    for (size_t i = 0; i < flat; i++)
    {
        auto x = i % this->size.x;
        auto y = i / this->size.x;
        auto pos = sf::Vector2f(
            this->pos.x + this->tileSize.x * x,
            this->pos.y + this->tileSize.y * y);

        this->tileSprite.setPosition(pos);
        window.draw(this->tileSprite);

        if (this->selectedTile == i)
        {
            this->selectionSprite.setPosition(pos + selectionOffset);
            window.draw(this->selectionSprite);
        }

        auto ballType = this->ballGrid[i];
        if (ballType != ::None)
        {
            auto sprite = this->ballSprites[ballType];
            sprite.setPosition(pos + ballOffset);
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
            if (this->selectedTile == -1 || this->ballGrid[clickedTile] != ::None)
                this->selectedTile = clickedTile;
            else if (this->selectedTile != -1 && this->moveBall(selectedTile, clickedTile))
            {
                this->selectedTile = -1;
                // todo: animate
                this->generateBalls(3);
                this->clearLines();
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
    auto flat = this->size.x * this->size.y;
    if (src > flat || dst > flat)
        throw std::runtime_error("src or dst out of grid bounds");
    if (this->ballGrid[dst] != ::None)
        return false;
    this->ballGrid[dst] = this->ballGrid[src];
    this->ballGrid.erase(src);
    return true;
}

// if generated tail is not empty, iterate every possible
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
            if (this->ballGrid[_tile] == ::None)
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

// todo: setPoints callback
void Board::clearLines(size_t minBalls)
{
    int points = 0;

    for (size_t i = 0; i < this->size.x; i++)
    {
        BallType prevBallType = ::None;
        size_t ballCount = 0;
        for (size_t j = 0; j < this->size.y; j++)
        {
            auto ballType = this->ballGrid[i * this->size.x + j];
            if (ballType == prevBallType)
                ballCount++;
            else
            {
                if (prevBallType != ::None && ballCount >= minBalls)
                {
                    points += ballCount;
                    for (int k = ballCount; k > 0; k--)
                        this->ballGrid.erase(i * this->size.x + j - k);
                }
                ballCount = 1;
            }
            prevBallType = ballType;
        }
    }

    for (size_t j = 0; j < this->size.x; j++)
    {
        BallType prevBallType = ::None;
        size_t ballCount = 0;
        for (size_t i = 0; i < this->size.y; i++)
        {
            auto ballType = this->ballGrid[i * this->size.x + j];
            if (ballType == prevBallType)
                ballCount++;
            else
            {
                if (prevBallType != ::None && ballCount >= minBalls)
                {
                    points += ballCount;
                    for (int k = ballCount; k > 0; k--)
                        this->ballGrid.erase((i - k) * this->size.x + j);
                }
                ballCount = 1;
            }
            prevBallType = ballType;
        }
    }

    if (points > 0)
        this->addCount(points);
}
