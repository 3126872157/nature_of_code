//
// Created by ken on 26-1-29.
//

#include "../include/conway.h"

sf::Vector2i Conway::wrap(const sf::Vector2i in) const
{
    sf::Vector2i out = in;
    if (in.x < 0) out.x = window_size_.x - 1;
    if (in.x >= window_size_.x) out.x = 0;
    if (in.y < 0) out.y = window_size_.y - 1;
    if (in.y >= window_size_.y) out.y = 0;
    return out;
}

void Conway::applyRule(const int x, const int y)
{
    int alive_sum = 0;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0) continue;
            sf::Vector2i t = wrap({x+i, y+j});
            alive_sum += state_[t.y][t.x];
        }
    }

    // if (state_[t.y][t.x] == 1) {
    //     new_state_[t.y][t.x] = (alive_sum == 2 || alive_sum == 3) ? 1 : 0;
    // } else {
    //     new_state_[t.y][t.x] = (alive_sum == 3) ? 1 : 0;
    // }

    if (alive_sum >= 4 || alive_sum <= 1)
    {
        new_state_[y][x] = 0;
    }
    if (alive_sum == 3)
    {
        new_state_[y][x] = 1;
    }
}


Conway::Conway(const sf::RenderWindow& window)
{
    state_.assign(window.getSize().y, std::vector<int>(window.getSize().y, 0));
    new_state_.assign(window.getSize().y, std::vector<int>(window.getSize().y, 0));
    generation_ = 0;
    clear_flag_ = false;
    window_size_ = window.getSize();
}

void Conway::init(sf::Vector2i pos, int state)
{
    state_[pos.y][pos.x] = state;
    new_state_[pos.y][pos.x] = state;
}

void Conway::randomInit()
{
}

void Conway::update(float dt)
{
    for (int j = 0; j < state_.size(); j++)
    {
        for (int i = 0; i < state_[j].size(); i++)
        {
            applyRule(i, j);
        }
    }
    state_.swap(new_state_);
}

void Conway::draw(sf::RenderWindow& window)
{
    sf::RectangleShape rect;
    for (int j = 0; j < state_.size(); j++)
    {
        for (int i = 0; i < state_[j].size(); i++)
        {
            if (state_[j][i] == 1)
            {
                rect.setFillColor(sf::Color::White);
                rect.setSize(sf::Vector2f(SIZE, SIZE));
                rect.setPosition(sf::Vector2f(i * SIZE, j * SIZE));
                window.draw(rect);
            }
        }
    }
}
