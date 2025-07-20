//
// Created by ken on 25-7-20.
//

#ifndef PARTICLE_H
#define PARTICLE_H

//sfml
#include "SFML/Graphics.hpp"

class Particle {
public:
    Particle();
    ~Particle();

    void update(float dt);
    void render(sf::RenderWindow &window);

    bool isDead() const;

    void addForce(const sf::Vector2f &force);

    void setPosition(const sf::Vector2f &position);
    void setVelocity(const sf::Vector2f &velocity);
    void setMass(const float mass);
    void setRadius(const float radius);
    void setColor(const sf::Color &color);

private:
    sf::Vector2f pos_;
    sf::Vector2f vel_;
    sf::Vector2f acc_;

    float mass_;
    float radius_;

    int lifespan_;
    bool alive_;

    sf::Color color_;
    sf::CircleShape entity_;
};

#endif //PARTICLE_H
