#pragma once
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameObject.hh"
#include "ResourceManager.hh"

#define _NUM_BALL_TYPES 5

enum BallType
{
    None,
    Baren,
    Ice,
    Lava,
    Terran,
};

class Board : GameObject
{
public:
    Board(sf::Vector2f pos, sf::Vector2u size, size_t initialBalls = 5);

    virtual void draw(sf::RenderWindow &window) override;
    virtual void handleEvent(const sf::Event &ev) override;

private:
    sf::Vector2f pos;
    sf::Vector2u size;
    // represents which tile contain which ball
    std::map<size_t, BallType> ballGrid;
    // sprites
    sf::Vector2u tileSize;
    sf::Sprite tileSprite;

    sf::Vector2u selectionSize;
    sf::Sprite selectionSprite;

    sf::Vector2u ballSize;
    std::map<BallType, sf::Sprite> ballSprites = {};
    // selected tile, used for moving balls
    size_t selectedTile = -1;

    // moves ball using A* algorithm, possibly performs an animation
    bool moveBall(size_t srt, size_t dst);
    // child of "mouseClicked" event handler
    bool getClickedTile(int mouseX, int mouseY, size_t &clickedTile);
    // adds new random balls to grid, if can't add returns false
    bool generateBalls(size_t numBalls);
    // finds vertical and horizonal lines of balls with same type
    // if finds line length > 5, clears it
    void clearLines(size_t minBalls = 5);
};
