#include "Ball.hh"
#include <map>
#include <iostream>

std::map<BallType, std::string> ballName = {
    {BallType::Baren, "baren"},
    {BallType::Ice, "ice"},
    {BallType::Lava, "lava"},
    {BallType::Terran, "terran"}};

Ball::Ball(ResourceManager &manager, const BallType &type, const sf::Vector2f &pos)
{
    auto textureName = "textures/" + ballName[type];
    this->ball = new sf::Sprite(*(sf::Texture *)manager.get(textureName));
    this->ball->setPosition(pos);
}

void Ball::draw(sf::RenderWindow &window)
{
    window.draw(*this->ball);
}

Ball Ball::random(ResourceManager &manager, sf::FloatRect &bounds)
{
}