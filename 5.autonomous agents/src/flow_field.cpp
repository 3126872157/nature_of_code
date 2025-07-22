//
// Created by ken on 25-7-22.
//

#include "../include/flow_field.h"

#include <iostream>

FlowField::FlowField(const int width, const int height, const float scale, const int resolution) {
    width_ = width / resolution;
    height_ = height / resolution;

    resolution_ = resolution;

    field_ = new float[width_ * height_];

    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            float fx = static_cast<float>(x) / static_cast<float>(width_);
            float fy = static_cast<float>(y) / static_cast<float>(height_);
            float val = perlin_.noise2D(fx * scale, fy * scale);
            val = (val + 1.f) / 2.f * 3.1415926 * 2.f;
            std::cout << val << std::endl;
            field_[x + width_ * y] = val;
        }
    }
}

FlowField::~FlowField() {
    delete[] field_;
}

float FlowField::getFlow(const sf::Vector2f &pos) const {
    int row = pos.y / resolution_;
    int col = pos.x / resolution_;

    if (col < 0 || col >= width_ || row < 0 || row >= height_) {
        return 0.f;  // 或者抛出异常、或使用默认方向
    }
    return field_[col + width_ * row];
}


float FlowField::getFlow(const float x, const float y) const {
    int row = y / resolution_;
    int col = x / resolution_;

    if (col < 0 || col >= width_ || row < 0 || row >= height_) {
        return 0.f;  // 或者抛出异常、或使用默认方向
    }
    return field_[col + width_ * row];
}

void FlowField::render(sf::RenderWindow& window) {
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            float val = field_[x + height_ * y];
            sf::RectangleShape shape(sf::Vector2f(resolution_, 1.0f));
            shape.setOrigin({resolution_ / 2.0f, 0.5f});
            shape.setRotation(sf::Angle(sf::radians(val)));
            shape.setPosition({(x+0.5) * resolution_, (y+0.5) * resolution_});
            window.draw(shape);
        }
    }
}