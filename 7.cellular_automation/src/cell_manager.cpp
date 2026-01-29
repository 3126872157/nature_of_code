//
// Created by ken on 26-1-29.
//

#include "../include/cell_manager.h"

#include "SFML/Graphics.hpp"

#define SIZE 10

int calState(int a, int b, int c)
{
    if (a == 0 && b == 0 && c == 0)
    {
        return 0;
    }
    else if (a == 0 && b == 0 && c == 1)
    {
        return 1;
    }
    else if (a == 0 && b == 1 && c == 0)
    {
        return 0;
    }
    else if (a == 0 && b == 1 && c == 1)
    {
        return 1;
    }
    else if (a == 1 && b == 0 && c == 0)
    {
        return 1;
    }
    else if (a == 1 && b == 0 && c == 1)
    {
        return 0;
    }
    else if (a == 1 && b == 1 && c == 0)
    {
        return 1;
    }
    else if (a == 1 && b == 1 && c == 1)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

CellManager::CellManager(const int size)
{
    state_ = std::vector<int>(size);
    generation_ = 0;
}

CellManager& CellManager::operator=(const CellManager& other)
{
    return *this;
}

CellManager::CellManager(const CellManager& other)
{
    state_ = other.state_;
    generation_ = other.generation_;
}


void CellManager::init(const int index, const int state)
{
    state_[index] = state;
}

void CellManager::update(float dt)
{
    std::vector<int> new_state(state_.size());
    for (int i = 0; i < state_.size(); i++)
    {
        printf("%d\n",i);
        if (i == 0)
        {
            new_state[i] = calState(0, state_[i], state_[i + 1]);
        }
        else if (i == state_.size() - 1)
        {
            new_state[i] = calState(state_[i - 1], state_[i], 0);
        }
        else
            new_state[i] = calState(state_[i-1], state_[i], state_[i + 1]);
    }
    state_ = new_state;
    generation_++;
}

void CellManager::draw(sf::RenderWindow& window)
{
    sf::RectangleShape cell;
    for (int i = 0; i < state_.size(); i++)
    {
        cell.setSize(sf::Vector2f(SIZE, SIZE));
        cell.setPosition(sf::Vector2f(i * SIZE, generation_ * SIZE));
        cell.setFillColor(state_[i] == 0 ? sf::Color::Black : sf::Color::White);
        window.draw(cell);
    }
}
