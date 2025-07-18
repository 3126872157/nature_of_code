//
// Created by ken on 25-7-14.
//

#include "../include/game.h"

Game::Game(const std::string &title, unsigned int width, unsigned int height) {
    //初始窗口
    window_ = sf::RenderWindow(sf::VideoMode({width, height}), title);
    window_.setFramerateLimit(60);

    //初始化
    spring_ = new Spring(200.0f, 10000.0f, 2.0f);
    bob_ = new Ball(30.0f, sf::Color::White);
    spring_->connect(bob_);

    spring_->setAnchor({static_cast<float>(width / 2), static_cast<float>(height / 2)});
    bob_->setPosition({930.0f, 600.0f});
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
    spring_->update(dt);
    bob_->addAccel(GRAVITY * sf::Vector2f(0.0f, 1.0f) / bob_->getMass());
    bob_->update(dt);
}

void Game::render() {
    window_.clear();

    //渲染
    spring_->render(window_);
    bob_->render(window_);

    window_.display();
}
