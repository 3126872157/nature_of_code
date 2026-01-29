//
// Created by ken on 26-1-29.
//

#include "../include/cell_manager.h"

#include "SFML/Graphics.hpp"

#define SIZE 10

int rule_num = 90;

int apply_rule(int a, int b, int c, int rule_number) {
    int i = (a << 2) | (b << 1) | c;
    return (rule_number >> i) & 1;
}

CellManager::CellManager(const int size) {
    state_ = std::vector<int>(size);
    generation_ = 0;
}

void CellManager::init(const int index, const int state) {
    state_[index] = state;
}

void CellManager::update(float dt) {
    std::vector<int> new_state(state_.size());
    for (int i = 0; i < state_.size(); i++) {
        if (i == 0) {
            new_state[i] = apply_rule(0, state_[i], state_[i + 1], rule_num);
        } else if (i == state_.size() - 1) {
            new_state[i] = apply_rule(state_[i - 1], state_[i], 0, rule_num);
        } else
            new_state[i] = apply_rule(state_[i - 1], state_[i], state_[i + 1], rule_num);
    }
    state_ = new_state;
    generation_++;
}

void CellManager::draw(sf::RenderWindow &window) {
    sf::RectangleShape cell;
    for (int i = 0; i < state_.size(); i++) {
        cell.setSize(sf::Vector2f(SIZE, SIZE));
        cell.setPosition(sf::Vector2f(i * SIZE, generation_ * SIZE));
        cell.setFillColor(state_[i] == 0 ? sf::Color::Black : sf::Color::White);
        window.draw(cell);
    }
}
