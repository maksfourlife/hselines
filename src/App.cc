#include "App.hh"

#define SIZE 474

App::App()
{
    this->window = new sf::RenderWindow(
        sf::VideoMode(sf::Vector2u(SIZE, SIZE)),
        "Lines");

    ResourceManager::getInstance().load("./assets");

    this->board = new Board(
        sf::Vector2f(5, 5),
        sf::Vector2u(8, 8));
}

void App::run()
{
    while (this->window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
            this->handleEvent(event);

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
    case sf::Event::Resized:
    {
        this->correctRatio(ev);
        break;
    }
    default:
        break;
    }
}

void App::correctRatio(const sf::Event &ev)
{
    auto width = ev.size.width;
    auto height = ev.size.height;
    auto max = width > height ? width : height;
    this->window->setSize(sf::Vector2u(max, max));
}

App::~App()
{
    delete this->board;
    delete this->window;
}