//
// Created by ken on 25-7-16.
//

#ifndef BALL_MANAGER_H
#define BALL_MANAGER_H

//std
#include <vector>
#include <random>

//project
#include "ball.h"

#define GRAVITY 100.0f

class BallManager {
public:
    explicit BallManager(size_t n);
    ~BallManager();

    void setRandomPosition(int width, int height);
    void update(float dt);
    void render(sf::RenderWindow &window);

private:


private:
    std::uniform_int_distribution<int> distribution_;
    std::mt19937 gen_;

    std::vector<Ball*> ball_list_ = {};
    std::vector<sf::Color> color_list_ = {
        sf::Color(255, 190, 11),
        sf::Color(251, 86, 7),
        sf::Color(255, 0, 110),
        sf::Color(131, 56, 236),
        sf::Color(58, 134, 255),
    };
};



#endif //BALL_MANAGER_H
