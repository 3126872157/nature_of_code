//
// Created by ken on 25-7-20.
//

#include "../include/vehicle_manager.h"

#include <iostream>

VehicleManager::VehicleManager(const int num) {
    num_ = num;
    separation_ = 80.0;
    coherence_ = 150.0;
    alignment_ = 300.0;
    for (int i = 0; i < num; i++) {
        list_.emplace_back(new Vehicle());
        list_.back()->setPosition({rand() * 1920.0f / RAND_MAX, rand() * 1080.0f / RAND_MAX});
        float angle = 2.0f * M_PI * rand() / RAND_MAX;
        float speed = rand() % 500;
        //list_.back()->setVelocity({speed * cosf(angle), speed * sinf(angle)});
    }
}

void VehicleManager::update(float dt) {
    for (auto &vehicle: list_) {
        //vehicle->addForce(force);
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
                if (dist.length() < separation_) {
                    sum += 1 / dist.length() * dist.normalized();
                    counter++;
                }
            }
        }
        if (counter > 0) {
            sum /= static_cast<float>(counter);
            myself->steer(sum);
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
                if (dist.length() < coherence_) {
                    sum += dist.length() * dist.normalized() * 0.01f;
                    counter++;
                }
            }
        }
        if (counter > 0) {
            sum /= static_cast<float>(counter);
            myself->steer(sum);
        }
    }
}

void VehicleManager::align() {
    for (auto &myself: list_) {
        sf::Vector2f align_speed = {};
        for (auto &other: list_) {
            if (myself != other) {
                auto dist = other->getPosition() - myself->getPosition();
                if (dist.length() < alignment_) {
                    align_speed += other->getVelocity();
                }
            }
        }
        align_speed /= static_cast<float>(list_.size());
        myself->steer(align_speed * 100.0f);
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