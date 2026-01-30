//
// Created by ken on 26-1-29.
//

#include "../include/cell_manager.h"

#include <iostream>
#include <random>

#include "SFML/Graphics.hpp"

#include "../include/game.h"



int apply_rule(int a, int b, int c, int rule_number) {
    int i = (a << 2) | (b << 1) | c;
    return (rule_number >> i) & 1;
}

CellManager::CellManager(const int size, const sf::RenderWindow& window) {
    state_ = std::vector<int>(size);
    generation_ = 0;
    clear_flag_ = false;
    rule_num_ = 30;

    if (!font_.openFromFile("/usr/share/fonts/opentype/ipaexfont-mincho/ipaexm.ttf"))
    {
        std::cerr << "Failed to open font file" << std::endl;
    }
    window_size_ = window.getSize();
}

void CellManager::init(const int index, const int state) {
    state_[index] = state;
}

void CellManager::update(float dt) {
    std::vector<int> new_state(state_.size());
    for (int i = 0; i < state_.size(); i++) {
        if (i == 0) {
            new_state[i] = apply_rule(0, state_[i], state_[i + 1], rule_num_);
        } else if (i == state_.size() - 1) {
            new_state[i] = apply_rule(state_[i - 1], state_[i], 0, rule_num_);
        } else
            new_state[i] = apply_rule(state_[i - 1], state_[i], state_[i + 1], rule_num_);
    }
    state_ = new_state;
    generation_++;

    //刷新
    if (generation_ >= window_size_.y / SIZE)
    {
        clear_flag_ = true;
        generation_ = 0;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 255);
        rule_num_ = dis(gen);

        state_ = std::vector<int>(window_size_.x / SIZE);
        init(window_size_.x / (2 * SIZE) - 1, 1);
    }
}

void CellManager::draw(sf::RenderWindow &window) {
    sf::RectangleShape cell;
    if (clear_flag_)
    {
        window.clear(sf::Color::Black);
        clear_flag_ = false;
    }
    for (int i = 0; i < state_.size(); i++) {
        cell.setSize(sf::Vector2f(SIZE, SIZE));
        cell.setPosition(sf::Vector2f(i * SIZE, generation_ * SIZE));
        cell.setFillColor(state_[i] == 0 ? sf::Color::Black : sf::Color::White);
        window.draw(cell);
    }
    printRule(window);
}

void CellManager::printRule(sf::RenderWindow& window)
{
    std::string ruleString = "Rule" + std::to_string(rule_num_);

    sf::Text text(font_, ruleString, 24);
    text.setFillColor(sf::Color::White); // 颜色
    text.setStyle(sf::Text::Bold);    // 样式（加粗）
    text.setPosition({10.f, 10.f}); // 设置在左上角 (偏移 10 像素避免贴边)

    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(120, 48));
    rect.setFillColor(sf::Color::Black);
    rect.setPosition({0, 0});

    window.draw(rect);
    window.draw(text);
}

