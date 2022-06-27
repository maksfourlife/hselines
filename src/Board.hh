#pragma once
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include "ResourceManager.hh"

#define _NUM_BALL_TYPES 5

/** Тип шара, используется для загрузки текстур и для составления линий */
enum BallType
{
    None,
    Baren,
    Ice,
    Lava,
    Terran,
};

/** Хранит расположение шаров, "зачеркивает линии", добавляет новые шары */
class Board
{
public:
    /**
     * @param pos позиция левого верхнего угла доски
     * @param size кол-во клеток по вертикали и горизонтали
     * @param addCount функция добавления очков - вызывается при "зачеркивании" линий
     * @param initialBalls кол-во шаров, создаваемых на старте
     */
    Board(
        sf::Vector2f pos,
        sf::Vector2u size,
        std::function<void(int)> addCount,
        size_t initialBalls = 5);

    void draw(sf::RenderWindow &window);
    void handleEvent(const sf::Event &ev);

private:
    sf::Vector2f pos;
    sf::Vector2u size;
    /** хранит пары (индекс шара, тип шара) */
    std::map<size_t, BallType> ballGrid;

    sf::Vector2u tileSize;
    sf::Sprite tileSprite;

    sf::Vector2u selectionSize;
    sf::Sprite selectionSprite;

    sf::Vector2u ballSize;
    std::map<BallType, sf::Sprite> ballSprites = {};

    // selected tile, used for moving balls
    size_t selectedTile = -1;
    // increment points callback
    std::function<void(int)> addCount;

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
