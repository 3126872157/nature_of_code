//
// Created by ken on 25-7-14.
//

#include "../include/random_walker.h"

#include <iostream>
#include <ostream>

RandomWalker::RandomWalker(const sf::RenderWindow &window) {
    entity_ = sf::RectangleShape(sf::Vector2f(2.0, 2.0));
    entity_.setFillColor(sf::Color::White);
    pos_ = sf::Vector2f(0, window.getSize().y / 2);
    entity_.setPosition(pos_);
    distribution = std::uniform_int_distribution<int>(-10, 10);

    perlin_ = new Perlin();
}

void RandomWalker::update(double dt) {
    //二维均匀分布随机游走，梅森旋转算法
    // int x_step = distribution(generator);
    // int y_step = distribution(generator);
    //
    // pos_ += sf::Vector2f(x_step, y_step);
    // entity_.setPosition(pos_);

    //一维柏林噪声
    auto noise = perlin_->noise1D((pos_.x ++) / 50);
    pos_.y = noise + 540;
    entity_.setPosition(pos_);
}

void RandomWalker::render(sf::RenderWindow &window) {
    window.draw(entity_);
}

sf::Vector2f RandomWalker::getPos() const {
    return pos_;
}
