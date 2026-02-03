//
// Created by ken on 25-7-14.
//

#include "../include/game.h"

Game::Game(const std::string& title, unsigned int width, unsigned int height)
{
    //初始窗口
    window_ = sf::RenderWindow(sf::VideoMode({width, height}), title);
    window_.setFramerateLimit(30);
    window_size_ = {static_cast<float>(width), static_cast<float>(height)};

    //初始化
    // cantor_ = new Cantor();
    // cantor_->draw(window_, {10.0f, 500.0f}, 1900.0f);
    koch_ = new KochCurve();
    koch_->draw(window_, {410.0f, 1000.0f}, 370, -1.047197551);
}

void Game::run()
{
    //游戏循环
    sf::Clock clock;
    while (window_.isOpen())
    {
        processEvents();
        update(clock.restart().asSeconds());
        render();
    }
}

void Game::processEvents()
{
    while (const std::optional event = window_.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window_.close();
        }
        //输入
    }
}

void Game::update(float dt)
{
}

void Game::render()
{
    //window_.clear();


    window_.display();
}

sf::Vector2f Game::getWindowSize()
{
    return window_size_;
}
