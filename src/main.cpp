#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>

#include "../include/Player.hpp"
#include "../include/Bullet.hpp"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({1600, 900}),
        "Endless Shooter"
    );

    window.setFramerateLimit(60);

    Player player;

    std::vector<Bullet> bullets;

    float fireCooldown = 0.15f;
    float fireTimer = 0.f;

    sf::Clock clock;

    while (window.isOpen())
    {
        float deltaTime =
            clock.restart().asSeconds();

        fireTimer += deltaTime;

        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        player.update(deltaTime, window);

        if (sf::Mouse::isButtonPressed(
                sf::Mouse::Button::Left) &&
            fireTimer >= fireCooldown)
        {
            bullets.emplace_back(
                player.getCenter(),
                player.getDirection()
            );

            fireTimer = 0.f;
        }

        for (auto& bullet : bullets)
        {
            bullet.update(deltaTime);
        }

        bullets.erase(
            std::remove_if(
                bullets.begin(),
                bullets.end(),
                [](const Bullet& bullet)
                {
                    return bullet.isOffScreen();
                }),
            bullets.end()
        );

        window.clear();

        for (auto& bullet : bullets)
        {
            bullet.draw(window);
        }

        player.draw(window);

        window.display();
    }

    return 0;
}