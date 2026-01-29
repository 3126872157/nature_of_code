//
// Created by ken on 25-7-14.
//

#ifndef GAME_H
#define GAME_H

//SFML
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics.hpp"

//project
#include "../include/cell_manager.h"

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
    sf::Vector2f window_size_;
    CellManager cm_;
};



#endif //GAME_H
