#include <doctest.h>
#define private public
#include <Board.hh>

TEST_CASE("1x1 generates 1 ball")
{
    Board board(
        sf::Vector2f(0, 0),
        sf::Vector2u(1, 1),
        [](int _) {});

    CHECK(board.generateBalls(1));
}

TEST_CASE("1x1 not generates 1 ball")
{
    Board board(
        sf::Vector2f(0, 0),
        sf::Vector2u(1, 1),
        [](int _) {});

    CHECK(board.generateBalls(2));
}
