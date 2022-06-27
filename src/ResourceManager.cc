#include "ResourceManager.hh"
#include <SFML/Graphics.hpp>

namespace fs = std::filesystem;

ResourceManager &ResourceManager::getInstance()
{
    static ResourceManager instance;
    return instance;
}

void ResourceManager::load(const fs::path &assets_path)
{
    for (auto &entry : fs::recursive_directory_iterator(assets_path))
    {
        auto path = entry.path();
        auto ext = path.extension();
        sf::GlResource *res;
        bool ok = false;
        if (ext == ".png")
        {
            auto texture = new sf::Texture();
            ok = texture->loadFromFile(path);
            res = (sf::GlResource *)texture;
        }
        else if (ext == ".ttf")
        {
            auto font = new sf::Font();
            ok = font->loadFromFile(path);
            res = (sf::GlResource *)font;
        }
        if (ok)
        {
            auto name = fs::relative(path, assets_path).string();
            name = name.substr(0, name.find_last_of("."));
            resources.insert({name, res});
        }
    }
}

const sf::GlResource *ResourceManager::get(const std::string &name)
{
    auto res = this->resources[name];
    if (res == nullptr)
        throw std::runtime_error("resource not found");
    return res;
}
