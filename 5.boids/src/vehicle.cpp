//
// Created by ken on 25-7-21.
//

#include "../include/vehicle.h"

#include <iostream>

//proj
#include "../include/utils.h"

Vehicle::Vehicle() {
    radius_ = 15.0f;
    mass_ = 1.0f;
    entity_ = sf::CircleShape(radius_, 3);
    max_speed_ = 500.0f; //500 pixel/s
    max_force_ = 1000.0f;
    setPosition(sf::Vector2f(960, 540));
    entity_.setOrigin({radius_, radius_});
}

void Vehicle::update(float dt){
    vel_ += acc_ * dt;
    constrain(vel_, max_speed_);
    pos_ += vel_ * dt;
    std::cout << vel_.length() << std::endl;

    wrapAround(pos_);

    acc_ = sf::Vector2f(0, 0);

    //方向，防抽搐振荡
    if (vel_.length() < 1e-1f)
        return;
    direction_ = angleBetween(vel_, sf::Vector2f(0, -1.0f));
}

void Vehicle::render(sf::RenderWindow &window) {
    sf::Angle angle = sf::radians(direction_);

    entity_.setPosition(pos_);
    entity_.setRotation(-angle);
    window.draw(entity_);
}

//Reynolds 转向理论，target 是目标位置
void Vehicle::steer(const sf::Vector2f &target) {
    auto t = target.normalized() * max_speed_;
    auto desire = (t - vel_);
    constrain(desire, max_force_);
    addForce(desire);
}

void Vehicle::seek(const sf::Vector2f &target) {
    auto t = target - pos_;

    //去除振荡
    if (t.length() < 1e-1f) {
        vel_ = {0, 0};
        return;
    }

    //减速圈
    if (t.length() < 200) {
        t = t.length() / 200.0f * t.normalized() * max_speed_;
    }else {
        t = t.normalized() * max_speed_;
    }

    //因为是速度期望转为力（加速度），没有直接物理意义，所以加上一个系数（魔法数字）
    auto desire = (t - vel_) * 10.0f;
    constrain(desire, max_force_);
    addForce(desire);
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

void Vehicle::setColor(const sf::Color &color) {
    color_ = color;
    entity_.setFillColor(color);
}

sf::Vector2f Vehicle::getPosition() const {
    return pos_;
}

sf::Vector2f Vehicle::getVelocity() const {
    return vel_;
}