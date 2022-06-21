#pragma once
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameObject.hh"
#include "ResourceManager.hh"

enum BallType
{
    Baren,
    Ice,
    Lava,
    Terran,
};

class Board : GameObject
{
public:
    Board(sf::Vector2f pos, sf::Vector2u size);

    virtual void draw(sf::RenderWindow &window) override;
    void handleEvent(const sf::Event &ev);

private:
    sf::Vector2f pos;
    sf::Vector2u size;
    // represents which tile contain which ball
    std::map<size_t, BallType> ballGrid;
    // sprites
    sf::Vector2u tileSize;
    sf::Sprite tileSprite;
    sf::Sprite selectionSprite;
    std::map<BallType, sf::Sprite> ballSprites = {};
    // selected tile, used for moving balls
    size_t selectedTile = -1;

    // moves ball using A* algorithm, possibly performs an animation
    bool moveBall(size_t srt, size_t dst);
    // child of "mouseClicked" event handler
    size_t getClickedTile(const sf::Event &ev);
};
