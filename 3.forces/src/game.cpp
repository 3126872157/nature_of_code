//
// Created by ken on 25-7-14.
//

#include "../include/game.h"

Game::Game(const std::string &title, unsigned int width, unsigned int height) {
    //初始窗口
    window_ = sf::RenderWindow(sf::VideoMode({width, height}), title);
    window_.setFramerateLimit(60);
    ball_ = new Ball(20.0, sf::Color::White);
    ball_->setPosition(sf::Vector2f(width / 2, height / 2));
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

void Game::update(float dt) {
    ball_->setAccel(sf::Vector2f(100.0f, 0.f));
    ball_->update(dt);
}

void Game::render() {
    window_.clear();

    //渲染
    ball_->render(window_);

    window_.display();
}
