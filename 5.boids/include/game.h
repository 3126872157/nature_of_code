//
// Created by ken on 25-7-14.
//

#ifndef GAME_H
#define GAME_H

//SFML
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics.hpp"

//project
#include "vehicle.h"
#include "vehicle_manager.h"

#define GRAVITY 10000.0f

class Game {
public:
    Game(const std::string &title, unsigned int width, unsigned int height);
    ~Game() = default;

    void run();
    //很傻逼，TODO:思考如何优化
    sf::Vector2f getWindowSize();
private:
    void processEvents();
    void update(float dt);
    void render();

private:
    sf::RenderWindow window_;
    Vehicle* vehicle_;
    VehicleManager* vehicle_manager_;
    sf::Vector2f target_;
    sf::Vector2f window_size_;
};



#endif //GAME_H
