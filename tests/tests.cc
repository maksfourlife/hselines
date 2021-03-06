#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define private public

#include <doctest.h>
#include "ResourceManager.hh"
#include "Board.hh"

TEST_CASE("ResourceManager: manager loads")
{
    auto resManager = ResourceManager::getInstance();
    resManager.load("./assets");

    CHECK(resManager.get("textures/baren") != nullptr);
    CHECK(resManager.get("textures/ice") != nullptr);
    CHECK(resManager.get("textures/lava") != nullptr);
    CHECK(resManager.get("textures/selection") != nullptr);
    CHECK(resManager.get("textures/terran") != nullptr);
    CHECK(resManager.get("textures/tile") != nullptr);
    CHECK(resManager.get("fonts/PressStart") != nullptr);
}

TEST_CASE("ResourceManager: throws on missing")
{
    auto resManager = ResourceManager::getInstance();
    CHECK_THROWS(resManager.get(""));
}

TEST_CASE("Board: 1x1 has 1-ball grid")
{
    auto board = Board::mock(
        sf::Vector2f(0, 0),
        sf::Vector2u(1, 1),
        sf::Vector2u(0, 0),
        sf::Vector2u(0, 0),
        sf::Vector2u(0, 0),
        [](int _) {}, 1);

    CHECK(board.ballGrid.size() == 1);
}

TEST_CASE("Board: 1x1 with 1 ball can add 1 and not 2")
{
    auto board = Board::mock(
        sf::Vector2f(0, 0),
        sf::Vector2u(1, 2),
        sf::Vector2u(0, 0),
        sf::Vector2u(0, 0),
        sf::Vector2u(0, 0),
        [](int _) {}, 1);

    CHECK(board.ballGrid.size() == 1);
    CHECK(board.generateBalls(1));
    CHECK(!board.generateBalls(1));
}

TEST_CASE("Board: not crosses empty line")
{
    auto board = Board::mock(
        sf::Vector2f(0, 0),
        sf::Vector2u(4, 4),
        sf::Vector2u(0, 0),
        sf::Vector2u(0, 0),
        sf::Vector2u(0, 0),
        [](int _)
        {
            throw std::runtime_error("crossed empty line");
        },
        1);

    board.clearLines(3);
}

TEST_CASE("Board: crosses one type line")
{
    bool sw;

    auto board = Board::mock(
        sf::Vector2f(0, 0),
        sf::Vector2u(4, 4),
        sf::Vector2u(0, 0),
        sf::Vector2u(0, 0),
        sf::Vector2u(0, 0),
        [&sw](int _)
        {
            sw = !sw;
        },
        1);

    board.ballGrid[0] = ::Lava;
    board.ballGrid[1] = ::Terran;
    board.ballGrid[2] = ::Lava;

    board.clearLines(3);
    CHECK(!sw);

    board.ballGrid[1] = ::Lava;
    sw = true;

    board.clearLines(3);
    CHECK(!sw);
}
