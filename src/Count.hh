#pragma once
#include <SFML/Graphics.hpp>

/** Объект-счетчик, отображает очки игрока */
class Count
{
public:
    /**
     * @param pos позиция левого верхнего угла счетчика
     */
    Count(sf::Vector2f pos);

    /** Добавляет/уменьшает счет на переданное кол-во очков
     * @param count кол-во очков
     */
    void addCount(int count);

    void draw(sf::RenderWindow &window);

private:
    sf::Text text;
    int count = 0;
};
