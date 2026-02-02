//
// Created by ken on 25-7-14.
//

#include "../include/game.h"
#include "../include/wolfram.h"

Game::Game(const std::string& title, unsigned int width, unsigned int height)
{
    //初始窗口
    window_ = sf::RenderWindow(sf::VideoMode({width, height}), title);
    window_.setFramerateLimit(30);
    window_size_ = {static_cast<float>(width), static_cast<float>(height)};

    //初始化
    // ca_wolfram_ = new Wolfram(width / SIZE, window_);
    // ca_wolfram_->init(width / (SIZE * 2) - 1, 1);
    // ca_wolfram_->draw(window_);

    ca_conway_ = new Conway(window_);
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
        if (auto* key = event->getIf<sf::Event::KeyPressed>())
        {
            if (key->code == sf::Keyboard::Key::C)
            {
                ca_conway_->setClearFlag();
            }
            if (key->code == sf::Keyboard::Key::Space)
            {
                ca_conway_->toggleRunFlag();
            }
            if (key->code == sf::Keyboard::Key::R)
            {
                ca_conway_->randomInit();
            }
            if (key->code == sf::Keyboard::Key::Up)
            {
                ca_conway_->changeFrameRate(true);
            }
            if (key->code == sf::Keyboard::Key::Down)
            {
                ca_conway_->changeFrameRate(false);
            }
        }
    }
}

void Game::update(float dt)
{
    // ca_wolfram_->update(dt);
    ca_conway_->update(dt);
}

void Game::render()
{
    if (!ca_wolfram_)
    {
        window_.clear();
    }

    //渲染
    // ca_wolfram_->draw(window_);
    ca_conway_->render(window_);

    window_.display();
}

sf::Vector2f Game::getWindowSize()
{
    return window_size_;
}
