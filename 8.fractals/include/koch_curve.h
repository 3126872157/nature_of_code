//
// Created by ken on 26-2-3.
//

#ifndef KOCH_CURVE_H
#define KOCH_CURVE_H

#include <cmath>

#define M_PI_3f (M_PIf / 3.0f)

class KochCurve
{
public:
    KochCurve() = default;
    ~KochCurve() = default;

public:
    //注意angle顺时针为正
    void draw(sf::RenderWindow& window, sf::Vector2f start, float len, float angle)
    {
        if (len >= 3)
        {
            triangle(window, start, len, angle);
            sf::Vector2f l = {len, 0};
            sf::Angle a = sf::radians(angle);
            draw(window, start + l.rotatedBy(a), len / 3.0f, angle - M_PI_3f);
            sf::Angle b = sf::radians(angle + M_PIf / 3.0f * 2.0f);
            draw(window, start + l.rotatedBy(a) * 3.0f + l.rotatedBy(b), len / 3.0f, angle + M_PI_3f);
        }else
        {
            sf::RectangleShape line;
            sf::Angle a = sf::radians(angle);
            sf::Vector2f l = {len, 0};
            line.setPosition(start);
            line.setSize(sf::Vector2f(len * 3, 1));
            line.setFillColor(sf::Color::White);
            line.setRotation(a);
            window.draw(line);
            line.setPosition(start + l.rotatedBy(a) * 3.0f);
            sf::Angle b = sf::radians(angle + M_PIf / 3.0f * 2.0f);
            line.setRotation(b);
            window.draw(line);
        }
    }

private
:
    void triangle(sf::RenderWindow& window, sf::Vector2f start, float len, float angle)
    {
        sf::RectangleShape line;
        sf::Angle a = sf::radians(angle);
        sf::Vector2f l = {len, 0};
        line.setPosition(start);
        line.setSize(sf::Vector2f(len, 1));
        line.setFillColor(sf::Color::White);
        line.setRotation(a);
        window.draw(line);
        line.setPosition(start + l.rotatedBy(a) * 2.0f);
        window.draw(line);
        line.setPosition(start + l.rotatedBy(a) * 3.0f);
        sf::Angle b = sf::radians(angle + M_PIf / 3.0f * 2.0f);
        line.setRotation(b);
        window.draw(line);
        line.setPosition(start + l.rotatedBy(a) * 3.0f + l.rotatedBy(b) * 2.0f);
        window.draw(line);
    }
};

#endif //KOCH_CURVE_H
