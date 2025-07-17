//
// Created by ken on 25-7-16.
//

#ifndef BALL_H
#define BALL_H

//std
#include <functional>

//sfml
#include "SFML/Graphics.hpp"

class Ball {
public:
    explicit Ball(const float radius, sf::Color color);
    ~Ball() = default;

    void update(float dt);
    void render(sf::RenderWindow &window);

    void setCalMass(std::function<float(float)> calMass);
    void setPosition(const sf::Vector2f &position);
    void addAccel(const sf::Vector2f &accel);
    void emptyAccel();

    sf::Vector2f getPosition() const;
    float getMass() const;

private:
    sf::Vector2f pos_;
    sf::Vector2f vel_;
    sf::Vector2f accel_;
    sf::Vector2f force_;

    float radius_;
    float mass_;
    //如何算质量：如 密度x半径 或 密度x半径平方
    std::function<float(float)> calMass_;

private:
    sf::Color color_;
    sf::CircleShape entity_;
};



#endif //BALL_H
