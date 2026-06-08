#include "../include/Player.hpp"

Player::Player()
{
    shape.setRadius(25.f);
    shape.setFillColor(sf::Color::Green);

    shape.setPosition({800.f, 450.f});

    speed = 400.f;
}

void Player::update(float deltaTime)
{
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        movement.y -= speed * deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        movement.y += speed * deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        movement.x -= speed * deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        movement.x += speed * deltaTime;

    shape.move(movement);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}