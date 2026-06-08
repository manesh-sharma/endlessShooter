#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>

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

    int score = 0;
    bool gameOver = false;

    sf::Clock clock;

    sf::Font font;

    if (!font.openFromFile("assets/ARLRDBD.TTF"))
    {
        std::cout << "Font failed to load\n";
        return -1;
    }

    sf::Text scoreText(font);
    scoreText.setCharacterSize(32);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({20.f, 20.f});

    sf::Text healthText(font);
    healthText.setCharacterSize(32);
    healthText.setFillColor(sf::Color::Green);
    healthText.setPosition({1440.f, 20.f});

    sf::Text gameOverText(font);
    gameOverText.setCharacterSize(80);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER\nPress R to Restart");
    gameOverText.setPosition({420.f, 320.f});

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

            if (const auto* keyPressed =
                event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code ==
                    sf::Keyboard::Key::R &&
                    gameOver)
                {
                    player = Player();

                    bullets.clear();
                    enemies.clear();

                    score = 0;

                    fireTimer = 0.f;
                    enemySpawnTimer = 0.f;

                    gameOver = false;
                }
            }
        }

        if (!gameOver)
        {
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

            // Enemy hits player
            for (size_t enemyIndex = 0;
                 enemyIndex < enemies.size();)
            {
                sf::Vector2f enemyPos =
                    enemies[enemyIndex].getCenter();

                sf::Vector2f playerPos =
                    player.getCenter();

                float dx =
                    enemyPos.x - playerPos.x;

                float dy =
                    enemyPos.y - playerPos.y;

                float distance =
                    std::sqrt(dx * dx + dy * dy);

                if (distance <
                    enemies[enemyIndex].getRadius()
                    + player.getRadius())
                {
                    player.takeDamage(10);

                    enemies.erase(
                        enemies.begin()
                        + enemyIndex);
                }
                else
                {
                    ++enemyIndex;
                }
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

                            score++;
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

            if (player.getHealth() <= 0)
            {
                gameOver = true;
            }
        }

        scoreText.setString(
            "Score: " +
            std::to_string(score)
        );

        healthText.setString(
            "HP: " +
            std::to_string(
                player.getHealth()
            )
        );

        window.clear();

        for (auto& bullet : bullets)
        {
            bullet.draw(window);
        }

        for (auto& enemy : enemies)
        {
            enemy.draw(window);
        }

        player.draw(window);

        window.draw(scoreText);
        window.draw(healthText);

        if (gameOver)
        {
            window.draw(gameOverText);
        }

        window.display();
    }

    return 0;
}