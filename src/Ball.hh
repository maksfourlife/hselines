#pragma once
#include "GameObject.hh"
#include "ResourceManager.hh"
#include <SFML/Graphics.hpp>

enum BallType
{
    Baren,
    Ice,
    Lava,
    Terran,
};

class Ball : GameObject
{
public:
    Ball(ResourceManager &manager, const BallType &type, const sf::Vector2f &pos);

    virtual void draw(sf::RenderWindow &window) override;

    /// generates "Ball" located in random tile with random
    static Ball random(ResourceManager &manager, sf::FloatRect &bounds);

private:
    sf::Sprite *ball;
};
