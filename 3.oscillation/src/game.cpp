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
    sub_spring_ = new Spring(200.0f, 10000.0f, 2.0f);
    bob_ = new Ball(30.0f, sf::Color::White);
    sub_bob_ = new Ball(30.0f, sf::Color::White);
    spring_->connect(bob_);
    sub_spring_->connect(sub_bob_);

    spring_->setAnchor({static_cast<float>(width / 2), 100.0f});
    bob_->setPosition({1000.0f, 400.0f});
    sub_bob_->setPosition({1500.0f, 600.0f});
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
    sub_spring_->setAnchor(bob_->getPosition());
    bob_->addAccel(GRAVITY * sf::Vector2f(0.0f, 1.0f) / bob_->getMass());
    bob_->addAccel(sub_spring_->getForceAnchor() / bob_->getMass());
    sub_spring_->update(dt);
    sub_bob_->addAccel(GRAVITY * sf::Vector2f(0.0f, 1.0f) / sub_bob_->getMass());
    bob_->update(dt);
    sub_bob_->update(dt);
}

void Game::render() {
    window_.clear();

    //渲染
    spring_->render(window_);
    sub_spring_->render(window_);
    bob_->render(window_);
    sub_bob_->render(window_);

    window_.display();
}
