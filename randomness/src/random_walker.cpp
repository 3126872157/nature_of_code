//
// Created by ken on 25-7-14.
//

#include "../include/random_walker.h"

#include <iostream>
#include <ostream>

RandomWalker::RandomWalker(const sf::RenderWindow &window) {
    entity_ = sf::RectangleShape(sf::Vector2f(2.0, 2.0));
    entity_.setFillColor(sf::Color::White);
    pos_ = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);
    entity_.setPosition(pos_);
    distribution = std::uniform_int_distribution<int>(-10, 10);
}

void RandomWalker::update(double dt) {
    int x_step = distribution(generator);
    int y_step = distribution(generator);

    pos_ += sf::Vector2f(x_step, y_step);
    entity_.setPosition(pos_);
}

void RandomWalker::render(sf::RenderWindow &window) {
    window.draw(entity_);
}

sf::Vector2f RandomWalker::getPos() const {
    return pos_;
}
