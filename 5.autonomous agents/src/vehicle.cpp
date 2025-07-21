//
// Created by ken on 25-7-21.
//

#include "../include/vehicle.h"

#include <iostream>

Vehicle::Vehicle() {
    radius_ = 15.0f;
    mass_ = 0.5f;
    entity_ = sf::CircleShape(radius_, 3);
    max_speed_ = 500.0f;
    max_force_ = 1000.0f;
    setVelocity(sf::Vector2f(0, -100.0f));    //正方向
    setPosition(sf::Vector2f(100, 100));
}

//utils
void constrain(sf::Vector2f& x, float max) {
    x = x.length() > max ? x.normalized() * x.length() : x;
}
//utils
float angleBetween(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    float dot = v1.x * v2.x + v1.y * v2.y;
    float det = v1.x * v2.y - v1.y * v2.x;  // 行列式

    return std::atan2(det, dot);  // 返回的是 [-π, π] 区间的弧度
}

void Vehicle::update(float dt){
    vel_ += acc_ * dt;
    constrain(vel_, max_speed_);
    pos_ += vel_ * dt;

    //方向
    direction_ = angleBetween(vel_, sf::Vector2f(0, -1.0f));

    acc_ = sf::Vector2f(0, 0);
}

void Vehicle::render(sf::RenderWindow &window) {
    sf::Angle angle = sf::radians(direction_);
    entity_.setPosition(pos_ + sf::Vector2f({-radius_,-radius_}));

    entity_.setRotation(-angle);
    window.draw(entity_);
}

void Vehicle::seek(const sf::Vector2f &target) {
    auto desire = target - pos_;
    steer_ = desire - vel_;
    constrain(steer_, max_force_);
    addForce(steer_);
    std::cout << steer_.x << ", " << steer_.y << std::endl;
}

void Vehicle::addForce(const sf::Vector2f &force) {
    acc_ += force / mass_;
}

void Vehicle::setPosition(const sf::Vector2f &position) {
    pos_ = position;
}

void Vehicle::setVelocity(const sf::Vector2f &velocity) {
    vel_ = velocity;
}

sf::Vector2f Vehicle::getPosition() const {
    return pos_;
}