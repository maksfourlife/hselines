#include "App.hh"

#define SIZE 590

App::App()
{
    this->window = new sf::RenderWindow(
        sf::VideoMode(sf::Vector2u(SIZE, SIZE)),
        "Lines",
        sf::Style::Default & ~sf::Style::Resize);

    ResourceManager::getInstance().load("./assets");

    this->board = new Board(
        sf::Vector2f(5, 5),
        sf::Vector2u(10, 10));
}

void App::run()
{
    while (this->window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            this->handleEvent(event);
            this->board->handleEvent(event);
        }

        this->window->clear(sf::Color(0xa8, 0xa8, 0xa8));

        this->board->draw(*this->window);

        this->window->display();
    }
}

void App::handleEvent(const sf::Event &ev)
{
    switch (ev.type)
    {
    case sf::Event::Closed:
    {
        this->window->close();
        break;
    }
    default:
        break;
    }
}

App::~App()
{
    delete this->board;
    delete this->window;
}