//
// Created by ken on 25-7-15.
//

#include "../include/perlin.h"

#include <cmath>
#include <iostream>
#include <bits/ostream.tcc>

double Perlin::noise1D(const double x) {
    int x1 = std::floor(x);
    int x2 = x1 + 1.0;

    auto grad = [this](const int x) {
        return perm[static_cast<size_t>(x) % perm.size()] * 1 - 122.5;
    };

    std::cout << grad(x1) << " " << grad(x2) << std::endl;

    double vec1 = x - x1;
    double vec2 = x - x2;

    double t = fade(vec1);

    return lerp(t, grad(x1) * vec1, grad(x2) * vec2);
}

double Perlin::fade(const double t) {
    //经典的 Perlin 使用的平滑函数
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double Perlin::lerp(const double t, const double a, const double b) {
    return a + t * (b - a);
}

