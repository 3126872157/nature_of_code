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
#include "vehicle.h"


class VehicleManager {
public:
    VehicleManager(const int num);
    ~VehicleManager() = default;

    void update(float dt);
    void render(sf::RenderWindow &window);

    void seek(sf::Vector2f target);

private:
    void separate(float t);
    void cohere(float t);
    void align(float t);

    int num_;
    float separation_;
    float coherence_;
    float alignment_;
    std::vector<Vehicle*> list_;
};



#endif //PARTICLE_MANAGER_H
