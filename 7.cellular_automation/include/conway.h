//
// Created by ken on 26-1-29.
//

#ifndef CONWAY_H
#define CONWAY_H

#include <random>
#include <vector>

#include "SFML/Graphics.hpp"

#define SIZE 15

class Conway
{
public:
    explicit Conway(const sf::RenderWindow& window);
    Conway(const Conway& other) = default;
    Conway& operator=(const Conway& other) = default;
    ~Conway() = default;

public:
    void init(sf::Vector2i pos, int state);
    void randomInit();
    void update(float dt);
    void draw(sf::RenderWindow& window);

private:
    void applyRule(int x, int y);
    sf::Vector2i wrap(sf::Vector2i in) const;

private:
    int generation_;
    std::vector<std::vector<int>> state_;
    std::vector<std::vector<int>> new_state_;
    bool clear_flag_;

    sf::Vector2u grid_size_; // 网格的宽和高（单位：个）
    sf::VertexArray vertices_; // 用于批量渲染
};


#endif //CONWAY_H
