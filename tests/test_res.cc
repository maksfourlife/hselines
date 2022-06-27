#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "ResourceManager.hh"

TEST_CASE("all resources loaded")
{
    auto res = ResourceManager::getInstance();
}
