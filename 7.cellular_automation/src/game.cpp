//
// Created by ken on 25-7-14.
//

#include "../include/game.h"
#include "../include/cell_manager.h"

Game::Game(const std::string &title, unsigned int width, unsigned int height) {
    //初始窗口
    window_ = sf::RenderWindow(sf::VideoMode({width, height}), title);
    window_.setFramerateLimit(60);
    window_size_ = {static_cast<float>(width), static_cast<float>(height)};

    //初始化
    // 使用 360 个元胞，对应圆周的 360 度
    cm_ = new CellManager(360, window_size_ * 0.5f);

    // 在圆环上设置几个初始种子，例如 3 个点均匀分布，会形成 3 重对称
    // 或者只设置 1 个点
    cm_->init(0, 1);
    // cm_->init(120, 1);
    // cm_->init(240, 1);
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
    cm_->update(dt);
}

void Game::render() {
    window_.clear(sf::Color::Black); // 清除屏幕，背景黑色

    //渲染
    cm_->draw(window_);

    window_.display();
}

sf::Vector2f Game::getWindowSize() {
    return window_size_;
}
