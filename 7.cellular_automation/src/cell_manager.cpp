//
// Created by ken on 26-1-29.
//

#include "../include/cell_manager.h"

#include <cmath>
#include "SFML/Graphics.hpp"

#define PI 3.14159265358979323846

int rule_num = 90;

int apply_rule(int a, int b, int c, int rule_number) {
    int i = (a << 2) | (b << 1) | c;
    return (rule_number >> i) & 1;
}

CellManager::CellManager(const int size, sf::Vector2f center) {
    state_ = std::vector<int>(size);
    generation_ = 0;
    center_ = center;
    // SFML 3.0: Quads 已被移除，改用 Triangles
    history_.setPrimitiveType(sf::PrimitiveType::Triangles);
    radius_step_ = 2.0f; // 每一代向外扩 2 像素
}

void CellManager::init(const int index, const int state) {
    state_[index] = state;
}

void CellManager::update(float dt) {
    // 1. 计算下一代状态 (使用环形边界条件)
    std::vector<int> new_state(state_.size());
    int size = static_cast<int>(state_.size());

    for (int i = 0; i < size; i++) {
        int left = state_[(i - 1 + size) % size];
        int middle = state_[i];
        int right = state_[(i + 1) % size];

        new_state[i] = apply_rule(left, middle, right, rule_num);
    }

    state_ = new_state;
    generation_++;

    // 2. 将当前代映射到极坐标并存入 VertexArray
    float current_radius = generation_ * radius_step_;
    float angle_step = 2.0f * PI / size;
    float cell_size = std::max(1.5f, current_radius * angle_step); // 动态调整细胞大小以填满圆环

    // 计算颜色 (Hue 随 generation 变化)
    // 每一代 Hue 偏移一点，形成彩虹圈
    float hue = fmod(generation_ * 2.0f, 360.0f);
    sf::Color color = hsv2rgb(hue, 0.8f, 1.0f);

    for (int i = 0; i < size; i++) {
        if (state_[i] == 1) {
            float angle = i * angle_step;

            // 计算中心位置
            float x = center_.x + current_radius * cos(angle);
            float y = center_.y + current_radius * sin(angle);

            sf::Vector2f pos(x, y);

            float half_w = cell_size / 2.0f;
            float half_h = radius_step_ / 2.0f;

            // 顶点偏移 (简化版，不旋转)
            // p1 --- p2
            // |       |
            // p4 --- p3

            // 旋转逻辑：
            // x' = x cos - y sin
            // y' = x sin + y cos
            // 这里的旋转角度是 angle + PI/2 (切线方向)

            // 顶点偏移
            sf::Vector2f p1 = pos + sf::Vector2f(cos(angle) * half_h - sin(angle) * half_w, sin(angle) * half_h + cos(angle) * half_w);
            sf::Vector2f p2 = pos + sf::Vector2f(cos(angle) * half_h - sin(angle) * -half_w, sin(angle) * half_h + cos(angle) * -half_w);
            sf::Vector2f p3 = pos + sf::Vector2f(cos(angle) * -half_h - sin(angle) * -half_w, sin(angle) * -half_h + cos(angle) * -half_w);
            sf::Vector2f p4 = pos + sf::Vector2f(cos(angle) * -half_h - sin(angle) * half_w, sin(angle) * -half_h + cos(angle) * half_w);

            // SFML 3.0: 使用聚合初始化，并且每个 Quad 拆分为两个 Triangle
            // Triangle 1: p1, p2, p3
            history_.append(sf::Vertex{p1, color});
            history_.append(sf::Vertex{p2, color});
            history_.append(sf::Vertex{p3, color});

            // Triangle 2: p3, p4, p1
            history_.append(sf::Vertex{p3, color});
            history_.append(sf::Vertex{p4, color});
            history_.append(sf::Vertex{p1, color});
        }
    }
}

void CellManager::draw(sf::RenderWindow &window) {
    window.draw(history_);
}

sf::Color CellManager::hsv2rgb(float h, float s, float v) {
    float c = v * s;
    float x = c * (1 - std::abs(fmod(h / 60.0f, 2) - 1));
    float m = v - c;

    float r = 0, g = 0, b = 0;

    if (h >= 0 && h < 60) {
        r = c; g = x; b = 0;
    } else if (h >= 60 && h < 120) {
        r = x; g = c; b = 0;
    } else if (h >= 120 && h < 180) {
        r = 0; g = c; b = x;
    } else if (h >= 180 && h < 240) {
        r = 0; g = x; b = c;
    } else if (h >= 240 && h < 300) {
        r = x; g = 0; b = c;
    } else {
        r = c; g = 0; b = x;
    }

    return sf::Color(static_cast<std::uint8_t>((r + m) * 255),
                     static_cast<std::uint8_t>((g + m) * 255),
                     static_cast<std::uint8_t>((b + m) * 255));
}
