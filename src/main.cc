#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    sf::Vector2u windowSize(474, 474);
    sf::RenderWindow window(sf::VideoMode(windowSize), "Lines");

    sf::Texture tileTexture;
    if (!tileTexture.loadFromFile("../assets/textures/Tile.png"))
    {
        throw std::runtime_error("failed to load textures.");
    }

    sf::Texture selectionTexture;
    if (!selectionTexture.loadFromFile("../assets/textures/Selection.png"))
    {
        throw std::runtime_error("failed to load textures.");
    }

    sf::Sprite tileSprite(tileTexture);
    sf::Sprite selectionSprite(selectionTexture);

    selectionSprite.setPosition(sf::Vector2f(10, 10));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                auto width = event.size.width;
                auto height = event.size.height;
                auto max = width > height ? width : height;
                window.setSize(sf::Vector2u(max, max));
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

        window.draw(selectionSprite);

        window.display();
    }

    return 0;
}