#include "../include/Player.hpp"
#include <cmath>

Player::Player()
{
    // Player body
    shape.setRadius(25.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition({800.f, 450.f});

    // Movement speed
    speed = 400.f;

    // Gun
    gun.setSize({40.f, 4.f});
    gun.setFillColor(sf::Color::White);

    // Rotate around left-center of rectangle
    gun.setOrigin({0.f, 2.f});
}

void Player::update(float deltaTime, sf::RenderWindow& window)
{
    sf::Vector2f movement(0.f, 0.f);

    // WASD Movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        movement.y -= speed * deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        movement.y += speed * deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        movement.x -= speed * deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        movement.x += speed * deltaTime;

    shape.move(movement);

    // Player center
    sf::Vector2f playerCenter(
        shape.getPosition().x + shape.getRadius(),
        shape.getPosition().y + shape.getRadius()
    );

    // Mouse position
    sf::Vector2i mousePixel =
        sf::Mouse::getPosition(window);

    sf::Vector2f mouseWorld =
        window.mapPixelToCoords(mousePixel);

    // Direction vector
    float dx = mouseWorld.x - playerCenter.x;
    float dy = mouseWorld.y - playerCenter.y;

    // Calculate angle
    float angle =
        std::atan2(dy, dx) * 180.f / 3.14159265f;

    // Position and rotate gun
    gun.setPosition(playerCenter);
    gun.setRotation(sf::degrees(angle));
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(gun);
    window.draw(shape);
}