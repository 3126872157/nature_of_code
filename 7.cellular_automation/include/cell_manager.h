//
// Created by ken on 26-1-29.
//

#ifndef CELL_MANAGER_H
#define CELL_MANAGER_H

#include <vector>

#include "SFML/Graphics.hpp"

class CellManager
{
public:
    explicit CellManager(int size, sf::Vector2f center);
    CellManager(const CellManager& other) = default;
    CellManager& operator=(const CellManager& other) = default;
    ~CellManager() = default;

public:
    void init(int index, int state);
    void update(float dt);
    void draw(sf::RenderWindow& window);

private:
    sf::Color hsv2rgb(float h, float s, float v);

private:
    int generation_;
    std::vector<int> state_;
    sf::Vector2f center_;
    sf::VertexArray history_; // 存储所有历史点
    float radius_step_; // 每一代半径增加的量
};

#endif //CELL_MANAGER_H
