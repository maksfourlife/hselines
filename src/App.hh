#pragma once
#include <SFML/Graphics.hpp>
#include "Board.hh"
#include "Count.hh"

class App
{
public:
    App();
    void run();

private:
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<Board> board;
    std::shared_ptr<Count> count;

    void handleEvent(const sf::Event &ev);
};
