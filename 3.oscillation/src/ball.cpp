//
// Created by ken on 25-7-16.
//

#include "../include/ball.h"

#include <iostream>

Ball::Ball(float radius, sf::Color color){
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
    emptyAccel();
}

void Ball::render(sf::RenderWindow &window){
    window.draw(entity_);
}

void Ball::setCalMass(std::function<float(float)> calMass){
    calMass_ = calMass;
    mass_ = calMass(radius_);
}

void Ball::setPosition(const sf::Vector2f &position){
    pos_ = position;
}

void Ball::setVelocity(const sf::Vector2f &velocity) {
    vel_ = velocity;
}

void Ball::addAccel(const sf::Vector2f &accel){
    accel_ += accel;
}

void Ball::emptyAccel()
{
    accel_ = sf::Vector2f(0.f, 0.f);
}

sf::Vector2f Ball::getPosition() const{
    return pos_ + sf::Vector2f(radius_, radius_);
}

float Ball::getMass() const{
    return mass_;
}

float Ball::getRadius() const {
    return radius_;
}