//
// Created by ken on 25-7-20.
//

#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H

//std
#include <vector>
#include <random>
#include <algorithm>

//sfml
#include "SFML/Graphics.hpp"

//project
#include "particle.h"

class ParticleManager {
public:
    ParticleManager();
    ~ParticleManager() = default;

    void update(float dt);
    void render(sf::RenderWindow &window);

    void spawnParticle();

    void setPosition(const sf::Vector2f& pos);
    void setEmit(const bool if_emit);

private:
    std::vector<Particle*> list_;

    sf::Vector2f spawn_pos_;

    float spawn_interval_;
    float spawn_radius_;

    bool emitting_;
};



#endif //PARTICLE_MANAGER_H
