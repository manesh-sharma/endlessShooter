#include "../include/Bullet.hpp"

Bullet::Bullet(
    sf::Vector2f startPosition,
    sf::Vector2f direction)
{
    shape.setRadius(5.f);
    shape.setFillColor(sf::Color::Yellow);

    shape.setPosition(startPosition);

    velocity = direction * 800.f;
}

void Bullet::update(float deltaTime)
{
    shape.move(velocity * deltaTime);
}

void Bullet::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

bool Bullet::isOffScreen() const
{
    sf::Vector2f pos = shape.getPosition();

    return pos.x < 0 ||
           pos.x > 1600 ||
           pos.y < 0 ||
           pos.y > 900;
}