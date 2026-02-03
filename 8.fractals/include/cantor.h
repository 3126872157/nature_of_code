//
// Created by ken on 26-2-3.
//

#ifndef CANTOR_H
#define CANTOR_H

class Cantor
{
public:
    Cantor() = default;
    ~Cantor() = default;

public:
    void draw(sf::RenderWindow &window, sf::Vector2f pos, float len)
    {
        if (len < 1) return;
        sf::RectangleShape rect(sf::Vector2f(len, 1));
        rect.setFillColor(sf::Color::White);
        rect.setPosition(pos);
        window.draw(rect);

        draw(window, sf::Vector2f(pos.x, pos.y + 20), len/3);
        draw(window, sf::Vector2f(pos.x + len*2/3, pos.y + 20), len/3);
    }

private:
};

#endif //CANTOR_H
