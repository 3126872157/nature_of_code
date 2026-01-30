//
// Created by ken on 25-7-14.
//

#ifndef GAME_H
#define GAME_H

//SFML
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics.hpp"

//project
#include "../include/conway.h"
#include "../include/wolfram.h"

class Game {
public:
    Game(const std::string &title, unsigned int width, unsigned int height);
    ~Game() = default;

    void run();
    //TODO：类与对象，不会用
    sf::Vector2f getWindowSize();
private:
    void processEvents();
    void update(float dt);
    void render();

private:
    sf::RenderWindow window_;
    sf::Vector2f window_size_;
    Wolfram* ca_wolfram_ = nullptr;
    Conway* ca_conway_;
};



#endif //GAME_H
