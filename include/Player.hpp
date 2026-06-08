#pragma once

#include <SFML/Graphics.hpp>

class Player
{
private:
    sf::CircleShape shape;
    sf::RectangleShape gun;
    float speed;

public:
    Player();

    void update(float deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};