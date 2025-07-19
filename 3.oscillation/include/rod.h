//
// Created by ken on 25-7-19.
//

#ifndef ROD_H
#define ROD_H

//std
#include <cmath>

//sfml
#include "SFML/Graphics.hpp"

//project
#include "ball.h"

class Rod {
public:
    explicit Rod(float length, float thick);
    ~Rod() = default;

    void connect(Ball* bob);
    void update(const float dt);
    void render(sf::RenderWindow &window);

    sf::Vector2f getForceEnd() const;
    sf::Vector2f getForceStart() const;

    void setStart(const sf::Vector2f& start);
    void setEnd(const sf::Vector2f& end);

    void setTotalForce(const sf::Vector2f& force);

private:
    float length_;
    float thick_;

    sf::Vector2f start_;
    sf::Vector2f end_;

    sf::Vector2f total_force_;

    float angle_;
    float angle_vel_;
    float angle_acc_;

    Ball* bob_;

    sf::RectangleShape entity_;
};

#endif //ROD_H
