#pragma once
#include <SFML/Graphics.hpp>
#include "Board.hh"

class App
{
public:
    App();
    ~App();
    void run();

private:
    sf::RenderWindow *window;
    Board *board;

    void handleEvent(const sf::Event &ev);
    void correctRatio(const sf::Event &ev);
};
