//
// Created by ken on 25-7-14.
//

#include "../include/game.h"

Game::Game(const std::string &title, unsigned int width, unsigned int height) {
    //初始窗口
    window_ = sf::RenderWindow(sf::VideoMode({width, height}), title);
    window_.setFramerateLimit(60);

    //初始化
    vehicle_manager_ = new VehicleManager(50);
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
        target_ = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window_));
    }
}

void Game::update(float dt) {
    //vehicle_manager_->seek(target_);
    vehicle_manager_->update(dt);
}

void Game::render() {
    window_.clear();

    //渲染
    //vehicle_->render(window_);
    vehicle_manager_->render(window_);

    window_.display();
}
