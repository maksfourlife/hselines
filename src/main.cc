#include <iostream>
#include <SFML/Window.hpp>

int main()
{
    sf::Vector2u size(600, 800);
    sf::Window window(sf::VideoMode(size), "Hello world!");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    }

    return 0;
}