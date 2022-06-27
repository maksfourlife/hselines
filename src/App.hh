#pragma once
#include <SFML/Graphics.hpp>
#include "Board.hh"
#include "Count.hh"

class App
{
public:
    App();
    ~App();
    void run();

private:
    sf::RenderWindow *window;
    Board *board;
    Count *count;

    void handleEvent(const sf::Event &ev);
};
