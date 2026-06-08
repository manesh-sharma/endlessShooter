#pragma once

#include <SFML/Graphics.hpp>

class Player
{
private:
    sf::CircleShape shape;
    sf::RectangleShape gun;

    float speed;
    int health;

public:
    Player();

    void update(float deltaTime, sf::RenderWindow& window);

    void draw(sf::RenderWindow& window);

    sf::Vector2f getCenter() const;

    sf::Vector2f getDirection() const;

    void takeDamage(int damage);

    int getHealth() const;

    float getRadius() const;
};