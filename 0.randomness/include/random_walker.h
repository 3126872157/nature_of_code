//
// Created by ken on 25-7-14.
//

#ifndef RANDOM_WALKER_H
#define RANDOM_WALKER_H

//stl
#include <random>

//SFML
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

//project
#include "perlin.h"

class RandomWalker {
public:
    explicit RandomWalker(const sf::RenderWindow &window);
    ~RandomWalker() = default;

    void update(double dt);
    void render(sf::RenderWindow &window);

    sf::Vector2f getPos() const;

private:
    sf::Vector2f pos_;
    sf::RectangleShape entity_;

private:
    Perlin* perlin_;
    std::mt19937 generator;
    std::uniform_int_distribution<int> distribution;
};

#endif //RANDOM_WALKER_H
