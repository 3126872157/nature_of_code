//
// Created by ken on 25-7-22.
//

#ifndef FLOW_FIELD_H
#define FLOW_FIELD_H

//sfml
#include "SFML/Graphics.hpp"

//project
#include "perlin.h"

class FlowField {
public:
    explicit FlowField(const int width, const int height, const float scale, const int resolution);
    ~FlowField();

    float getFlow(const float x, const float y) const;
    float getFlow(const sf::Vector2f &pos) const;

private:
    int width_;
    int height_;
    int resolution_;

    float* field_;

    Perlin perlin_;
};



#endif //FLOW_FIELD_H
