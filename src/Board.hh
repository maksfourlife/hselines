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

    static Board mock(
        sf::Vector2f pos,
        sf::Vector2u size,
        sf::Vector2u tileSize,
        sf::Vector2u selectionSize,
        sf::Vector2u ballSize,
        std::function<void(int)> addCount,
        size_t initialBalls);

private:
    Board() {}

    sf::Vector2f pos;
    sf::Vector2u size;
    /** таблица шаров: хранит пары (индекс шара, тип шара) */
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

    /** Передвигает шар и (todo) проверяет можно ли построить маршрут
     * @param src клетка откуда двигать шар
     * @param dst клетка куда двигать шар
     * @returns получилось ли передвинуть шар
     */
    bool moveBall(size_t src, size_t dst);

    /** Вычисляет нажатую ячейку по (x,y) нажания
     * @param mouseX x-компонента вектора курсора мыши
     * @param mouseT y-компонента
     * @param clickedTile записываемый номер ячейки
     * @returns флаг ошибки
     */
    bool getClickedTile(int mouseX, int mouseY, size_t &clickedTile);

    /** Генерирует шары и заносит в таблицу
     * @param numBalls кол-во шаров
     */
    bool generateBalls(size_t numBalls);

    /** Находит в таблице шаров "линии", убирает их и начисляет баллы
     * @param minBalls мин. кол-во шаров в линии
     */
    void clearLines(size_t minBalls = 5);
};
