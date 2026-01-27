//
// Created by ken on 25-7-20.
//

#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H

//std
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

//sfml
#include "SFML/Graphics.hpp"

//project
#include "vehicle.h"
#include "quad_tree.hpp"
#include "../include/utils.h"


class VehicleManager {
public:
    VehicleManager(const int num, sf::Vector2f window);
    ~VehicleManager() = default;

    void update(float dt);
    void render(sf::RenderWindow &window);

    void seek(sf::Vector2f target);

private:
    // 合并后的群聚行为计算函数
    void applyFlocking(float t);

private:
    int num_;
    float separation_;
    float coherence_;
    float alignment_;
    std::vector<Vehicle*> list_;

    QuadTree<Vehicle*> qt_root_;
    QuadTreeItem<Vehicle*> qt_item_;
    std::vector<QuadTreeItem<Vehicle*>> candidates_;
};



#endif //PARTICLE_MANAGER_H