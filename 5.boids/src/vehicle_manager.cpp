//
// Created by ken on 25-7-20.
//

#include "../include/vehicle_manager.h"
#include "../include/utils.h"

#include <iostream>

VehicleManager::VehicleManager(const int num) {
    num_ = num;
    separation_ = 45.0;
    coherence_ = 75.0;
    alignment_ = 105.0;
    for (int i = 0; i < num; i++) {
        list_.emplace_back(new Vehicle());
        list_.back()->setPosition({rand() * 1920.0f / RAND_MAX, rand() * 1080.0f / RAND_MAX});
        float angle = 2.0f * M_PI * rand() / RAND_MAX;
        float speed = rand() % 100 + 50;
        list_.back()->setVelocity({speed * cosf(angle), speed * sinf(angle)});
    }
}

void VehicleManager::update(float dt) {
    static float t;
    t += dt;

    // 1. 计算所有力
    separate(t);
    align(t);
    cohere(t);

    // 2. 统一更新物理状态
    for (auto &vehicle: list_) {
        vehicle->update(dt);
    }
}

void VehicleManager::separate(float t) {
    for (auto &myself: list_) {
        sf::Vector2f sum = {};
        int counter = 0;
        for (auto &other: list_) {
            if (myself != other) {
                auto dist = myself->getPosition() - other->getPosition();
                float d = dist.length();
                if (d < separation_ && d > 0) {
                    // 权重与距离成反比
                    sum += dist.normalized() / d;
                    counter++;
                }
            }
        }
        if (counter > 0) {
            sum /= static_cast<float>(counter);
            // 分离力通常需要较大权重
            if (sum.length() > 0) {
                sum = sum.normalized(); // 任意系数，代表期望速度方向
                myself->steer(sum, getSin(3, 5, 1, t)); // 这里的 k 是力的系数
            }
        }
    }
}

void VehicleManager::cohere(float t) {
    for (auto &myself: list_) {
        sf::Vector2f sum = {};
        int counter = 0;
        for (auto &other: list_) {
            if (myself != other) {
                auto dist = other->getPosition() - myself->getPosition();
                if (dist.length() < coherence_ && dist.length() > 0) {
                    // 累加绝对位置
                    sum += other->getPosition();
                    counter++;
                }
            }
        }
        if (counter > 0) {
            sum /= static_cast<float>(counter);
            // 传入目标位置，让 seek 去计算期望速度
            myself->seek(sum, getSin(0.4, 0.5, 1, t));
        }
    }
}

void VehicleManager::align(float t) {
    for (auto &myself: list_) {
        sf::Vector2f align_speed = {};
        int counter = 0;
        for (auto &other: list_) {
            if (myself != other) {
                auto dist = other->getPosition() - myself->getPosition();
                auto my_vel = myself->getVelocity();
                if (dist.length() < alignment_ && dist.dot(my_vel) / (my_vel.length() * dist.length()) < 0.5f) {
                    align_speed += other->getVelocity();
                    counter++;
                }
            }
        }
        if (counter > 0) {
            // 修复：除以 counter 而不是 list_.size()
            align_speed /= static_cast<float>(counter);

            // 期望速度就是邻居的平均速度
            if (align_speed.length() > 0) {
                align_speed = align_speed.normalized();
                myself->steer(align_speed, getSin(1, 2, 1, t));
            }
        }
    }
}

void VehicleManager::seek(sf::Vector2f target) {
    for (const auto &vehicle: list_) {
        vehicle->seek(target, 0.3f);
    }
}


void VehicleManager::render(sf::RenderWindow &window) {
    for (const auto &vehicle: list_) {
        vehicle->render(window);
    }
}
