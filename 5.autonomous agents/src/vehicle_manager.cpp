//
// Created by ken on 25-7-20.
//

#include "../include/vehicle_manager.h"

VehicleManager::VehicleManager(const int num) {
    num_ = num;
    separation_ = 80.0;
    coherence_ = 150.0;
    alignment_ = 300.0;
    for (int i = 0; i < num; i++) {
        list_.emplace_back(new Vehicle());
        list_.back()->setPosition({rand() * 1920.0f / RAND_MAX, rand() * 1080.0f / RAND_MAX});
        list_.back()->setVelocity({rand() * 500.0f, rand() * 500.0f});
    }
    flow_filed_ = new FlowField(1920, 1080, 4, 120);
}

void VehicleManager::update(float dt) {
    for (auto &vehicle : list_) {
        auto angle = flow_filed_->getFlow(vehicle->getPosition());
        float len = 50000.0f;    //随便设置的一个很大速度
        sf::Vector2f force = sf::Vector2f(len * std::cos(angle), len * std::sin(angle));
        //vehicle->seek(force);
        //vehicle->addForce(force);
        separate();
        cohere();
        align();
        vehicle->update(dt);
    }
}

void VehicleManager::separate() {
    for (auto &myself : list_) {
        for (auto &other : list_) {
            if (myself != other) {
                auto dist = other->getPosition() - myself->getPosition();
                if (dist.length() < separation_) {
                    myself->addForce(-dist * 0.5f);
                    other->addForce(dist * 0.5f);
                }
            }
        }
    }
}

void VehicleManager::cohere() {
    for (auto &myself : list_) {
        for (auto &other : list_) {
            if (myself != other) {
                auto dist = other->getPosition() - myself->getPosition();
                if (dist.length() < coherence_) {
                    myself->addForce(dist * 0.1f);
                    other->addForce(-dist * 0.1f);
                }
            }
        }
    }
}

void VehicleManager::align() {
    for (auto &myself : list_) {
        sf::Vector2f align_speed = {};
        for (auto &other : list_) {
            if (myself != other) {
                auto dist = other->getPosition() - myself->getPosition();
                if (dist.length() < alignment_) {
                    align_speed += other->getVelocity();
                }
                align_speed /= static_cast<float>(list_.size());
            }
        }
        myself->seek(align_speed * 1.5f);
    }
}

void VehicleManager::render(sf::RenderWindow &window) {
    flow_filed_->render(window);
    for (const auto &vehicle: list_) {
        vehicle->render(window);
    }
}