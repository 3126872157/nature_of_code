//
// Created by ken on 25-7-19.
//

#include "../include/rod.h"

#include <iostream>

#include "../include/game.h"

//utils
float angleBetween(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    float dot = v1.x * v2.x + v1.y * v2.y;
    float det = v1.x * v2.y - v1.y * v2.x;  // 行列式

    return std::atan2(det, dot);  // 返回的是 [-π, π] 区间的弧度
}

Rod::Rod(const float length, const float thick = 2.0f){
    length_ = length;
    thick_ = thick;
}

void Rod::connect(Ball* bob)
{
    bob_ = bob;
    end_ = bob_->getPosition();
    sf::Vector2f dir = start_ - end_;
    float theta = atan2(-dir.x, -dir.y);
    angle_ = theta;
}

void Rod::update(const float dt)
{
    if (bob_ != nullptr)
    {
        end_ = bob_->getPosition();
        sf::Vector2f dir = start_ - end_;
        std::cout << dir.length() << std::endl;
        float theta = angleBetween(total_force_, -dir);
        angle_acc_ = GRAVITY * sin(theta) / length_;
        angle_vel_ += angle_acc_ * dt;
        angle_ += angle_vel_ * dt;
        bob_->setPosition({static_cast<float>(start_.x + length_ * sin(angle_)),
                              static_cast<float>(start_.y + length_ * cos(angle_))});
    }
}

void Rod::render(sf::RenderWindow& window)
{
    if (bob_ != nullptr)
        end_ = bob_->getPosition();
    auto dir = end_ - start_;
    float dist = dir.length();
    entity_ = sf::RectangleShape({dist, thick_});
    sf::Angle angle = sf::radians(std::atan2(dir.y, dir.x));
    entity_.setPosition({start_.x, start_.y - thick_ / 2});
    entity_.setRotation(angle);
    window.draw(entity_);
    bob_->render(window);
}



sf::Vector2f Rod::getForceEnd() const
{
    if (bob_ == nullptr)
        throw std::runtime_error("Rod does not have a bob");
    sf::Vector2f dir = start_ - end_;
    float theta = angleBetween(total_force_, -dir);
    return total_force_.length() * std::cos(theta) * dir.normalized();
}

sf::Vector2f Rod::getForceStart() const
{
    return -1.0f * getForceEnd();
}

void Rod::setEnd(const sf::Vector2f& end)
{
    end_ = end;
}

void Rod::setStart(const sf::Vector2f& start)
{
    start_ = start;
}

void Rod::setTotalForce(const sf::Vector2f& force) {
    total_force_ = force;
}
