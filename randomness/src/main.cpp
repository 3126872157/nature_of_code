#include <SFML/Graphics.hpp>
#include "../include/random_walker.h"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920, 1080}), "Random walker");
    window.setFramerateLimit(60);
    window.setPosition({1000,1000});

    RandomWalker walker(window);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        //window.clear();
        walker.step();
        window.draw(walker.entity_);
        window.display();
    }
}
