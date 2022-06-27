#include "doctest.h"
#include "ResourceManager.hh"

auto resManager = ResourceManager::getInstance();

TEST_CASE("manager loads")
{
    resManager.load("./assets");

    CHECK(resManager.get("textures/baren") != nullptr);
    CHECK(resManager.get("textures/ice") != nullptr);
    CHECK(resManager.get("textures/lava") != nullptr);
    CHECK(resManager.get("textures/selection") != nullptr);
    CHECK(resManager.get("textures/terran") != nullptr);
    CHECK(resManager.get("textures/tile") != nullptr);
    CHECK(resManager.get("fonts/PressStart") != nullptr);
}

TEST_CASE("throws on missing")
{
    // CHECK_THROWS(resManager.get(""));
}
