#pragma once

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <filesystem>

class ResourceManager
{
public:
    ResourceManager(const std::filesystem::path &path);
    const sf::GlResource *get(const std::string &name);

private:
    std::map<std::string, sf::GlResource *> resources;
};
