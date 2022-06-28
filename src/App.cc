#include "App.hh"
#define SIZE 590

App::App()
{
    this->window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(sf::Vector2u(SIZE, SIZE)),
        "Lines",
        sf::Style::Default & ~sf::Style::Resize);

    ResourceManager::getInstance().load("./assets");

    this->count = std::make_shared<Count>(sf::Vector2f(20, 20));
    auto count = this->count;

    this->board = std::make_unique<Board>(
        sf::Vector2f(5, 5),
        sf::Vector2u(10, 10),
        [&count](int added)
        {
            count->addCount(added);
        });
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

        this->window->clear(sf::Color(0x18, 0x17, 0x3C));

        this->board->draw(*this->window);
        this->count->draw(*this->window);

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
