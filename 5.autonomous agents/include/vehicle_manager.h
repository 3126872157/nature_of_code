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
#include "flow_field.h"

class VehicleManager {
public:
    VehicleManager(const int num);
    ~VehicleManager() = default;

    void update(float dt);
    void render(sf::RenderWindow &window);

private:
    void separate();
    int num_;
    float separation_;
    std::vector<Vehicle*> list_;
    FlowField* flow_filed_;
};



#endif //PARTICLE_MANAGER_H
