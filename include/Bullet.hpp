#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;

public:
    Bullet(
        sf::Vector2f startPosition,
        sf::Vector2f direction
    );

    void update(float deltaTime);

    void draw(sf::RenderWindow& window);

    bool isOffScreen() const;
};