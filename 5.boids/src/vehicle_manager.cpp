//
// Created by ken on 25-7-20.
//

#include "../include/vehicle_manager.h"

#include <iostream>

VehicleManager::VehicleManager(const int num) {
    num_ = num;
    separation_ = 50.0;
    coherence_ = 100.0;
    alignment_ = 100.0;
    for (int i = 0; i < num; i++) {
        list_.emplace_back(new Vehicle());
        list_.back()->setPosition({rand() * 1920.0f / RAND_MAX, rand() * 1080.0f / RAND_MAX});
        float angle = 2.0f * M_PI * rand() / RAND_MAX;
        float speed = rand() % 100;
        list_.back()->setVelocity({speed * cosf(angle), speed * sinf(angle)});
    }
}

void VehicleManager::update(float dt) {
    // 1. 计算所有力
    separate();
    align();
    cohere();

    // 2. 统一更新物理状态
    for (auto &vehicle: list_) {
        vehicle->update(dt);
    }
}

void VehicleManager::separate() {
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
                sum = sum.normalized() * 1.5f; // 任意系数，代表期望速度方向
                myself->steer(sum, 0.5f); // 这里的 k 是力的系数
            }
        }
    }
}

void VehicleManager::cohere() {
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
            myself->seek(sum);
        }
    }
}

void VehicleManager::align() {
    for (auto &myself: list_) {
        sf::Vector2f align_speed = {};
        int counter = 0;
        for (auto &other: list_) {
            if (myself != other) {
                auto dist = other->getPosition() - myself->getPosition();
                if (dist.length() < alignment_) {
                    align_speed += other->getVelocity();
                    counter++;
                }
            }
        }
        if (counter > 0){
            // 修复：除以 counter 而不是 list_.size()
            align_speed /= static_cast<float>(counter);

            // 期望速度就是邻居的平均速度
            if (align_speed.length() > 0) {
                align_speed = align_speed.normalized();
                myself->steer(align_speed, 2.0f);
            }
        }
    }
}

void VehicleManager::seek(sf::Vector2f target) {
    for (const auto &vehicle: list_) {
        vehicle->seek(target);
    }
}


void VehicleManager::render(sf::RenderWindow &window) {
    for (const auto &vehicle: list_) {
        vehicle->render(window);
    }
}