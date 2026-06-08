#include "../include/Player.hpp"
#include <cmath>

Player::Player()
{
    shape.setRadius(25.f);
    shape.setFillColor(sf::Color::Green);

    shape.setPosition({800.f, 450.f});

    speed = 400.f;

    gun.setSize({40.f, 4.f});
    gun.setFillColor(sf::Color::White);

    gun.setOrigin({0.f, 2.f});
}

void Player::update(float deltaTime, sf::RenderWindow& window)
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

    sf::Vector2f playerCenter(
        shape.getPosition().x + shape.getRadius(),
        shape.getPosition().y + shape.getRadius()
    );

    sf::Vector2i mousePixel =
        sf::Mouse::getPosition(window);

    sf::Vector2f mouseWorld =
        window.mapPixelToCoords(mousePixel);

    float dx = mouseWorld.x - playerCenter.x;
    float dy = mouseWorld.y - playerCenter.y;

    float angle =
        std::atan2(dy, dx) * 180.f / 3.14159265f;

    gun.setPosition(playerCenter);
    gun.setRotation(sf::degrees(angle));
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(gun);
    window.draw(shape);
}

sf::Vector2f Player::getCenter() const
{
    return
    {
        shape.getPosition().x + shape.getRadius(),
        shape.getPosition().y + shape.getRadius()
    };
}

sf::Vector2f Player::getDirection() const
{
    float angle =
        gun.getRotation().asDegrees() *
        3.14159265f / 180.f;

    return
    {
        std::cos(angle),
        std::sin(angle)
    };
}