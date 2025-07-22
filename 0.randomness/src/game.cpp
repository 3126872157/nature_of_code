//
// Created by ken on 25-7-14.
//

#include "../include/game.h"

#include <iostream>

Game::Game(const std::string &title, unsigned int width, unsigned int height) {
    //初始窗口
    window_ = sf::RenderWindow(sf::VideoMode({width, height}), title);
    window_.setFramerateLimit(60);

    randomWalker_ = new RandomWalker(window_);

    float scale = 8.0;
    sf::Image image({width, height}, sf::Color::Black);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float val = perlin.noise2D(x * scale / width, y * scale / height); // scale 控制粗糙度
            val = (val + 1.f) / 2.f; // [-1,1] → [0,1]
            std::cout << val << std::endl;
            auto gray = val * 255.0f;
            image.setPixel({x, y}, sf::Color(gray, gray, gray));
        }
    }

    sf::Texture texture;
    texture.loadFromImage(image);

    sf::Sprite sprite(texture);
    window_.draw(sprite);
    window_.display();
}

void Game::run() {
    //游戏循环
    sf::Clock clock;
    while (window_.isOpen()) {
        processEvents();
        update(clock.restart().asSeconds());
        render();
    }
}

void Game::processEvents() {
    while (const std::optional event = window_.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window_.close();
        }
        //输入

    }
}

void Game::update(double dt) {
    //randomWalker_->update(dt);
}

void Game::render() {
    //window_.clear();

    //渲染
    //randomWalker_->render(window_);

    window_.display();
}
