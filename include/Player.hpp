#pragma once

#include <SFML/Graphics.hpp>

class Player
{
private:
    sf::CircleShape shape;
    float speed;

public:
    Player();

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
};