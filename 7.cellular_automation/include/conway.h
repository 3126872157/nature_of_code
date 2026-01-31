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
    void write(sf::Vector2i pos, int state);
    void drawChar(int startX, int startY, const std::vector<std::string>& mask);
    void randomInit();
    void update(float dt);
    void render(sf::RenderWindow& window);

    void setClearFlag();
    void toggleRunFlag();
    void draw(sf::Vector2i mouse_pos);
    void changeFrameRate(bool is_up);

private:
    void applyRule(int x, int y);
    sf::Vector2i wrap(sf::Vector2i in) const;
    void clear();
    void initDrawUI();

private:
    int generation_;
    std::vector<std::vector<int>> state_;
    std::vector<std::vector<int>> new_state_;

    sf::Vector2u grid_size_; // 网格的宽和高（单位：个）
    sf::VertexArray vertices_; // 用于批量渲染

    float t_max = 0.0167;

    // ui
    bool clear_flag_;
    bool run_flag_;
};


#endif //CONWAY_H
