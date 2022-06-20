#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "ResourceManager.hh"

void correct_ratio(sf::Window &window, sf::Event &ev)
{
    auto width = ev.size.width;
    auto height = ev.size.height;
    auto max = width > height ? width : height;
    window.setSize(sf::Vector2u(max, max));
}

int main()
{
    ResourceManager manager("./assets");

    sf::Vector2u windowSize(474, 474);
    sf::RenderWindow window(sf::VideoMode(windowSize), "Lines");

    sf::Sprite tileSprite;
    tileSprite.setTexture(*(sf::Texture *)manager.get("textures/tile"));

    sf::Sprite planetSprite(*(sf::Texture *)manager.get("textures/lava"));
    planetSprite.setPosition(sf::Vector2f(10, 10));

    sf::Sprite selectionSprite(*(sf::Texture *)manager.get("textures/selection"));
    selectionSprite.setPosition(sf::Vector2f(7, 7));

    auto show = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
            {
                window.close();
                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                show = !show;
                break;
            }
            case sf::Event::Resized:
            {
                correct_ratio(window, event);
                break;
            }
            default:
                break;
            }
        }

        window.clear(sf::Color(0xa8, 0xa8, 0xa8));

        for (auto i = 0; i < 8; i++)
            for (auto j = 0; j < 8; j++)
            {
                tileSprite.setPosition(sf::Vector2f(i * 58 + 5, j * 58 + 5));
                window.draw(tileSprite);
            }

        if (show)
            window.draw(selectionSprite);
        window.draw(planetSprite);

        window.display();
    }

    return 0;
}