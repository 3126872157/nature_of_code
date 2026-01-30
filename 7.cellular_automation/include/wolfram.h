//
// Created by ken on 26-1-29.
//

#ifndef CELL_MANAGER_H
#define CELL_MANAGER_H

#include <vector>

#include "SFML/Graphics.hpp"

#define SIZE 2

class Wolfram
{
public:
    explicit Wolfram(const int size, const sf::RenderWindow& window);
    Wolfram(const Wolfram& other) = default;
    Wolfram& operator=(const Wolfram& other) = default;
    ~Wolfram() = default;

public:
    void init(int index, int state);
    void update(float dt);
    void draw(sf::RenderWindow& window);

private:
    int applyRule(int a, int b, int c, int rule_number);
    void printRule(sf::RenderWindow& window) const;

private:
    int generation_;
    std::vector<int> state_;
    bool clear_flag_;
    int rule_num_;
    sf::Font font_;
    sf::Vector2u window_size_;
};

#endif //CELL_MANAGER_H
