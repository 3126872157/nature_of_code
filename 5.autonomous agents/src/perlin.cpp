//
// Created by ken on 25-7-15.
//

#include "../include/perlin.h"

#include <cmath>
#include <iostream>

float Perlin::noise1D(const float x) {
    int x1 = std::floor(x);
    int x2 = x1 + 1.0;

    auto grad = [this](const int x) {
        return perm[static_cast<size_t>(x) % perm.size()] * 1 - 122.5;
    };

    float vec1 = x - x1;
    float vec2 = x - x2;

    float t = fade(vec1);

    return lerp(t, grad(x1) * vec1, grad(x2) * vec2);
}

float Perlin::noise2D(const float x, const float y) {
    int x1 = std::floor(x);
    int x2 = x1 + 1.0;
    int y1 = std::floor(y);
    int y2 = y1 + 1.0;

    auto grad = [this](const float x, const float y) {
        sf::Vector2f vec(0, 0);
        vec.x = x * 127.1 + y * 311.7;
        vec.y = x * 269.5 + y * 183.3;

        float sin0 = sin(vec.x) * 43758.5453123;
        float sin1 = sin(vec.y) * 43758.5453123;
        vec.x = (sin0 - floor(sin0)) * 2.0 - 1.0;
        vec.y = (sin1 - floor(sin1)) * 2.0 - 1.0;

        return vec.normalized();
    };

    auto g0 = grad(x1, y1);
    auto g1 = grad(x2, y1);
    auto g2 = grad(x1, y2);
    auto g3 = grad(x2, y2);

    sf::Vector2f t(x, y);
    auto v0 = t - sf::Vector2f(x1, y1);
    auto v1 = t - sf::Vector2f(x2, y1);
    auto v2 = t - sf::Vector2f(x1, y2);
    auto v3 = t - sf::Vector2f(x2, y2);

    float p0 = g0.dot(v0);
    float p1 = g1.dot(v1);
    float p2 = g2.dot(v2);
    float p3 = g3.dot(v3);

    float top = lerp(fade(x - x1), p0, p1);
    float bottom = lerp(fade(x - x1), p2, p3);
    return lerp(fade(y - y1), top, bottom);
}

float Perlin::fade(const float t) {
    //经典的 Perlin 使用的平滑函数
    return t * t * t * (t * (t * 6 - 15) + 10);
}

template<typename T>
T Perlin::lerp(const float t, const T a, const T b) {
    return a + t * (b - a);
}
