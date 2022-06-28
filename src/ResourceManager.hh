#pragma once

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <filesystem>

/** Синглтон для загрузки текстур/шрифтов и сохранения на протяжении действия программы */
class ResourceManager
{
public:
    static ResourceManager &getInstance();
    /** Загружает ресурсы из указанной директории сохраняя в имени путь
     * Пример: textures/Lava.png -> .get("textures/lava.png")
     */
    void load(const std::filesystem::path &path);
    /** Получает из внутреннего хранлища ресурс и проверяет что он загружен
     */
    const void *get(const std::string &name);

private:
    std::map<std::string, std::shared_ptr<void>> resources;
};
