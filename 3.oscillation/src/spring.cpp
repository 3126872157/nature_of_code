//
// Created by ken on 25-7-18.
//

#include "../include/spring.h"

Spring::Spring(const float origin_length, const float k, const float thick = 2.0f) {
    origin_len_ = origin_length;
    k_ = k;
    thickness_ = thick;
}

void Spring::connect(Ball *bob) {
    bob_ = bob;
}

void Spring::update(const float dt) {
    if (bob_ != nullptr) {
        end_ = bob_->getPosition();
        auto spring_force = getForceEnd();
        bob_->addAccel(spring_force / bob_->getMass());
    }
}

void Spring::render(sf::RenderWindow &window) {
    if (bob_ != nullptr)
        end_ = bob_->getPosition();
    auto dir = end_ - anchor_;
    float dist = dir.length();
    entity_ = sf::RectangleShape({dist, thickness_});
    sf::Angle angle = sf::radians(std::atan2(dir.y, dir.x));
    entity_.setPosition({anchor_.x, anchor_.y - thickness_ / 2});
    entity_.setRotation(angle);
    window.draw(entity_);
}

sf::Vector2f Spring::getForceEnd() const {
    sf::Vector2f dir = anchor_ - end_;
    float delta = dir.length() - origin_len_;
    return k_ * delta * dir.normalized();
}

sf::Vector2f Spring::getForceAnchor() const {
    sf::Vector2f dir = end_ - anchor_;
    return k_ * (dir.length() - origin_len_) * dir.normalized();
}

void Spring::setAnchor(const sf::Vector2f &anchor) {
    anchor_ = anchor;
}

void Spring::setEnd(const sf::Vector2f& end) {
    end_ = end;
}
