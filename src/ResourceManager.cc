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
        std::shared_ptr<void> res;
        bool ok = false;
        if (ext == ".png")
        {
            auto texture = std::make_shared<sf::Texture>();
            ok = texture->loadFromFile(path);
            res = texture;
        }
        else if (ext == ".ttf")
        {
            auto font = std::make_shared<sf::Font>();
            ok = font->loadFromFile(path);
            res = font;
        }
        if (ok)
        {
            auto name = fs::relative(path, assets_path).string();
            name = name.substr(0, name.find_last_of("."));
            this->resources[name] = res;
        }
    }
}

const void *ResourceManager::get(const std::string &name)
{
    auto res = this->resources[name];
    if (res == nullptr)
        throw std::runtime_error(
            "resource " + name + " not found");
    return res.get();
}
