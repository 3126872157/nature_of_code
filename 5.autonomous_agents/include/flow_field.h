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
    //scale是给柏林噪声的，越小越规律，分辨率越低
    explicit FlowField(const int width, const int height, const float scale, const int resolution);
    ~FlowField();

    void render(sf::RenderWindow& window);

    float getFlow(const float x, const float y) const;
    float getFlow(const sf::Vector2f &pos) const;

private:
    int width_;
    int height_;
    //越小，流场分辨越高，请填30的倍数（1920，1080的公倍数）
    int resolution_;

    float* field_;

    Perlin perlin_;
};



#endif //FLOW_FIELD_H
