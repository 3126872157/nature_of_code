//
// Created by ken on 25-7-16.
//

#include "../include/ball.h"

Ball::Ball(double radius, sf::Color color){
    radius_ = radius;
    mass_ = radius * radius;

    color_ = color;
    entity_ = sf::CircleShape(radius);
    entity_.setFillColor(color_);
}

void Ball::update(float dt){
    //fixme：哪个先更新，v 还是 s
    pos_ += vel_ * dt + 0.5f * accel_ * dt * dt;
    vel_ += accel_ * dt;
    entity_.setPosition(pos_);
}

void Ball::render(sf::RenderWindow &window){
    window.draw(entity_);
}

void Ball::setCalMass(std::function<double(double)> calMass){
    calMass_ = calMass;
    mass_ = calMass(radius_);
}

void Ball::setPosition(const sf::Vector2f &position){
    pos_ = position;
}

void Ball::setAccel(const sf::Vector2f &accel){
    accel_ = accel;
}

sf::Vector2f Ball::getPosition() const{
    return pos_;
}