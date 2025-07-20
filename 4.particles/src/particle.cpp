//
// Created by ken on 25-7-20.
//

#include "../include/particle.h"

Particle::Particle() {
    alive_ = true;
    mass_ = 50;
    radius_ = 5.0f;
    entity_ = sf::CircleShape(radius_);
    entity_.setFillColor(sf::Color::White);
    lifespan_ = 50;
}

Particle::~Particle() {
    lifespan_ = -1;
    alive_ = false;
}

void Particle::update(float dt) {
    vel_ += acc_ * dt;
    pos_ += vel_ * dt;
    lifespan_ --;

    if (lifespan_ <= 0) {
        alive_ = false;
    }

    acc_ = sf::Vector2f(0,0);
}

void Particle::render(sf::RenderWindow &window) {
    entity_.setPosition(pos_ + sf::Vector2f({-radius_,-radius_}));
    window.draw(entity_);
}

bool Particle::isDead() const {
    return !alive_;
}

void Particle::addForce(const sf::Vector2f &force) {
    acc_ = force / mass_;
}

void Particle::setPosition(const sf::Vector2f &position) {
    pos_ = position;
}

void Particle::setVelocity(const sf::Vector2f &velocity) {
    vel_ = velocity;
}

void Particle::setMass(const float mass) {
    mass_ = mass;
}

void Particle::setRadius(const float radius) {
    radius_ = radius;
}

void Particle::setColor(const sf::Color &color) {
    color_ = color;
}

