//
// Created by ken on 25-7-14.
//

#ifndef GAME_H
#define GAME_H

//SFML
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics.hpp"

//project
#include "random_walker.h"

class Game {
public:
    Game(const std::string &title, unsigned int width, unsigned int height);
    ~Game() = default;

    void run();
private:
    void processEvents();
    void update(double dt);
    void render();

private:
    sf::RenderWindow window_;
    RandomWalker* randomWalker_;
};



#endif //GAME_H
