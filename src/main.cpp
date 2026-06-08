#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <cmath>

#include "../include/Player.hpp"
#include "../include/Bullet.hpp"
#include "../include/Enemy.hpp"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({1600, 900}),
        "Endless Shooter"
    );

    window.setFramerateLimit(60);

    Player player;

    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;

    float fireCooldown = 0.15f;
    float fireTimer = 0.f;

    float enemySpawnTimer = 0.f;
    float enemySpawnCooldown = 2.f;

    sf::Clock clock;

    while (window.isOpen())
    {
        float deltaTime =
            clock.restart().asSeconds();

        fireTimer += deltaTime;
        enemySpawnTimer += deltaTime;

        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        player.update(deltaTime, window);

        // Spawn enemies
        if (enemySpawnTimer >= enemySpawnCooldown)
        {
            int side = rand() % 4;

            sf::Vector2f spawnPos;

            switch (side)
            {
            case 0:
                spawnPos =
                {
                    0.f,
                    static_cast<float>(rand() % 900)
                };
                break;

            case 1:
                spawnPos =
                {
                    1600.f,
                    static_cast<float>(rand() % 900)
                };
                break;

            case 2:
                spawnPos =
                {
                    static_cast<float>(rand() % 1600),
                    0.f
                };
                break;

            default:
                spawnPos =
                {
                    static_cast<float>(rand() % 1600),
                    900.f
                };
                break;
            }

            enemies.emplace_back(spawnPos);

            enemySpawnTimer = 0.f;
        }

        // Automatic shooting
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

        // Update bullets
        for (auto& bullet : bullets)
        {
            bullet.update(deltaTime);
        }

        // Update enemies
        for (auto& enemy : enemies)
        {
            enemy.update(
                deltaTime,
                player.getCenter()
            );
        }

        // Bullet vs Enemy collision
        for (size_t bulletIndex = 0;
             bulletIndex < bullets.size();)
        {
            bool bulletRemoved = false;

            for (size_t enemyIndex = 0;
                 enemyIndex < enemies.size();
                 ++enemyIndex)
            {
                sf::Vector2f bulletPos =
                    bullets[bulletIndex].getPosition();

                sf::Vector2f enemyPos =
                    enemies[enemyIndex].getCenter();

                float dx =
                    bulletPos.x - enemyPos.x;

                float dy =
                    bulletPos.y - enemyPos.y;

                float distance =
                    std::sqrt(dx * dx + dy * dy);

                if (distance <
                    enemies[enemyIndex].getRadius())
                {
                    bool enemyDead =
                        enemies[enemyIndex]
                        .takeDamage(40);

                    bullets.erase(
                        bullets.begin()
                        + bulletIndex);

                    bulletRemoved = true;

                    if (enemyDead)
                    {
                        enemies.erase(
                            enemies.begin()
                            + enemyIndex);
                    }

                    break;
                }
            }

            if (!bulletRemoved)
            {
                ++bulletIndex;
            }
        }

        // Remove off-screen bullets
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

        // Draw bullets
        for (auto& bullet : bullets)
        {
            bullet.draw(window);
        }

        // Draw enemies
        for (auto& enemy : enemies)
        {
            enemy.draw(window);
        }

        // Draw player
        player.draw(window);

        window.display();
    }

    return 0;
}