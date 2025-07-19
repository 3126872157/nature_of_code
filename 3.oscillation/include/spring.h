//
// Created by ken on 25-7-18.
//

#ifndef SPRING_H
#define SPRING_H

//std
#include <cmath>

//sfml
#include "SFML/Graphics.hpp"

//project
#include "ball.h"

class Spring {
public:
    explicit Spring(float origin_length, float k, float thick);
    ~Spring() = default;

    void connect(Ball* bob);
    void update(const float dt);
    void render(sf::RenderWindow &window);

    sf::Vector2f getForceEnd() const;
    sf::Vector2f getForceAnchor() const;

    void setAnchor(const sf::Vector2f& anchor);
    void setEnd(const sf::Vector2f& end);

private:
    float origin_len_;
    float current_len_;

    float k_;

    sf::Vector2f anchor_;
    sf::Vector2f end_;

    Ball* bob_;

    sf::RectangleShape entity_;
    float thickness_;
};



#endif //SPRING_H
