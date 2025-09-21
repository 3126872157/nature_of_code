//
// Created by ken on 25-7-21.
//

#ifndef VEHICLE_H
#define VEHICLE_H

//std
#include <cmath>

//sfml
#include "SFML/Graphics.hpp"

class Vehicle {
public:
    explicit Vehicle();
    ~Vehicle() = default;

    void update(float dt);
    void render(sf::RenderWindow &window);

    //k影响速度期望转化为转向力的因子
    void steer(const sf::Vector2f &target, const float k);
    void seek(const sf::Vector2f &position);
    void addForce(const sf::Vector2f &accel);

    void setPosition(const sf::Vector2f &position);
    void setVelocity(const sf::Vector2f &velocity);
    void setColor(const sf::Color &color);

    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;

private:
    sf::Vector2f pos_;
    sf::Vector2f vel_;
    sf::Vector2f acc_;

    sf::Vector2f steer_;

    float mass_;
    float radius_;
    float direction_;

    float max_speed_;
    float max_force_;

    sf::Color color_;
    sf::CircleShape entity_;
};



#endif //VEHICLE_H
