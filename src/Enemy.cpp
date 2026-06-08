#include "../include/Enemy.hpp"
#include <cmath>

Enemy::Enemy(sf::Vector2f startPosition)
{
    shape.setRadius(20.f);
    shape.setFillColor(sf::Color::Red);

    shape.setPosition(startPosition);

    speed = 150.f;
    health = 40;
}

void Enemy::update(
    float deltaTime,
    sf::Vector2f playerPosition)
{
    sf::Vector2f enemyCenter =
    {
        shape.getPosition().x + shape.getRadius(),
        shape.getPosition().y + shape.getRadius()
    };

    sf::Vector2f direction =
    {
        playerPosition.x - enemyCenter.x,
        playerPosition.y - enemyCenter.y
    };

    float length =
        std::sqrt(
            direction.x * direction.x +
            direction.y * direction.y
        );

    if (length != 0.f)
    {
        direction /= length;
    }

    shape.move(direction * speed * deltaTime);
}

void Enemy::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

sf::Vector2f Enemy::getCenter() const
{
    return
    {
        shape.getPosition().x + shape.getRadius(),
        shape.getPosition().y + shape.getRadius()
    };
}

float Enemy::getRadius() const
{
    return shape.getRadius();
}

bool Enemy::takeDamage(int damage)
{
    health -= damage;

    return health <= 0;
}