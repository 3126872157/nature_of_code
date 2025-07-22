//
// Created by ken on 25-7-20.
//

#include "../include/particle_manager.h"

VehicleManager::VehicleManager() {
    emitting_ = false;
    spawn_interval_ = 0.01;
}

void VehicleManager::update(float dt) {
    static float count = 0;
    if (emitting_) {
        count += dt;
        if (count >= spawn_interval_) {
            spawnParticle();
            count = 0;
        }
    }

    list_.erase(std::remove_if(list_.begin(), list_.end(),
                               [](const Particle *p) {
                                   return p->isDead();
                               }), list_.end());

    for (const auto &particle: list_) {
        //施加力（效果）
        particle->addForce(sf::Vector2f(0, 10000.0f));
        particle->update(dt);
    }
}

void VehicleManager::render(sf::RenderWindow &window) {
    for (const auto &particle: list_) {
        particle->render(window);
    }
}

void VehicleManager::spawnParticle() {
    list_.emplace_back(new Particle());
    list_.back()->setPosition(spawn_pos_);
    //fixme：随机函数要改
    list_.back()->setVelocity(sf::Vector2f(-rand() * 100.0f / RAND_MAX + 50.0f, -rand() * 100.0f / RAND_MAX + 50.0f));
}

void VehicleManager::setPosition(const sf::Vector2f &pos) {
    spawn_pos_ = pos;
}

void VehicleManager::setEmit(const bool if_emit) {
    emitting_ = if_emit;
}
