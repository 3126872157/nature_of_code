//
// Created by ken on 2025/9/20.
//

#ifndef BOIDS_UTILS_H
#define BOIDS_UTILS_H

#include "SFML/System/Vector2.hpp"
#include <cmath>

inline void constrain(sf::Vector2f& x, float max) {
    if (x.length() > max) {
        x = x.normalized() * max;
    }
}

inline float angleBetween(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    float dot = v1.x * v2.x + v1.y * v2.y;
    float det = v1.x * v2.y - v1.y * v2.x;  // 行列式

    return std::atan2(det, dot);  // 返回的是 [-π, π] 区间的弧度
}

inline void wrapAround(sf::Vector2f& pos) {
    if (pos.x > 1920.0f) {
        pos.x = 0;
    } else if (pos.x < 0) {
        pos.x = 1920.0f;
    }

    if (pos.y > 1080.0f) {
        pos.y = 0;
    } else if (pos.y < 0) {
        pos.y = 1080.0f;
    }
}

inline sf::Vector2f setMag(const sf::Vector2f &v, float m) {
    if (v.length() == 0) return v;
    sf::Vector2f n = v.normalized();
    return n * m;
}

inline float getSin(float magnitude, float offset, float omega, float t)
{
    return magnitude * std::sin(omega * t) + offset;
}

#endif //BOIDS_UTILS_H