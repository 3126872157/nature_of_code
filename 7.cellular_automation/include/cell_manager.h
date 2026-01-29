//
// Created by ken on 26-1-29.
//

#ifndef CELL_MANAGER_H
#define CELL_MANAGER_H

#include <vector>

#include "SFML/Graphics.hpp"

class CellManager
{
public:
    explicit CellManager(const int size);
    CellManager(const CellManager& other) = default;
    CellManager& operator=(const CellManager& other) = default;
    ~CellManager() = default;

public:
    void init(int index, int state);
    void update(float dt);
    void draw(sf::RenderWindow& window);

private:
    int generation_;
    std::vector<int> state_;
};

#endif //CELL_MANAGER_H
