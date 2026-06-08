#include <SFML/Graphics.hpp>
#include "../include/Player.hpp"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({1600, 900}),
        "Endless Shooter"
    );

    window.setFramerateLimit(60);

    Player player;

    sf::Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        player.update(deltaTime);

        window.clear();

        player.draw(window);

        window.display();
    }

    return 0;
}