#pragma once

#include <SFML/Graphics.hpp>

class Enemy
{
private:
    sf::CircleShape shape;
    float speed;
    int health;

public:
    Enemy(sf::Vector2f startPosition);

    void update(
        float deltaTime,
        sf::Vector2f playerPosition
    );

    void draw(sf::RenderWindow& window);

    sf::Vector2f getCenter() const;

    float getRadius() const;

    bool takeDamage(int damage);
};