//
// Created by ken on 25-7-19.
//

#include "../include/rod.h"

#include "../include/game.h"

Rod::Rod(const float length, const float thick = 2.0f){
    length_ = length;
    thick_ = thick;
}

void Rod::connect(Ball* bob)
{
    bob_ = bob;
}

void Rod::update(const float dt)
{
    if (bob_ != nullptr)
    {
        end_ = bob_->getPosition();
        auto force = getForceEnd();
        bob_->addAccel(force / bob_->getMass());
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
}



sf::Vector2f Rod::getForceEnd() const
{
    if (bob_ == nullptr)
        throw std::runtime_error("Rod does not have a bob");
    sf::Vector2f dir = start_ - end_;
    float theta = atan2(-dir.y, -dir.x);
    return std::cos(theta) * bob_->getMass() * GRAVITY * dir.normalized();
}

sf::Vector2f Rod::getForceStart() const
{
    return - getForceEnd();
}

void Rod::setEnd(const sf::Vector2f& end)
{
    end_ = end;
}

void Rod::setStart(const sf::Vector2f& start)
{
    start_ = start;
}
