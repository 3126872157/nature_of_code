//
// Created by ken on 25-7-14.
//

#ifndef RANDOM_WALKER_H
#define RANDOM_WALKER_H

#include <random>

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

class RandomWalker {
public:
    explicit RandomWalker(const sf::RenderWindow &window);
    ~RandomWalker() = default;

    void step();
    sf::Vector2f getPos() const;


    sf::RectangleShape entity_;

private:
    sf::Vector2f pos_;

private:
    std::mt19937 generator;
    std::uniform_int_distribution<int> distribution;
};

#endif //RANDOM_WALKER_H
