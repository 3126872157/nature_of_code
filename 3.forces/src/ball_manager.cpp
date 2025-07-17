//
// Created by ken on 25-7-16.
//

#include "../include/ball_manager.h"

BallManager::BallManager(size_t n){
    distribution_ = std::uniform_int_distribution<int>(-20, 20);
    for(size_t i = 0; i < n; i++)
    {
        float r = 30.0 + distribution_(gen_);
        //NOTE：不要用下标访问，还没分配空间，会段错
        ball_list_.emplace_back(new Ball(r, color_list_[i % color_list_.size()]));
    }
}

void BallManager::setRandomPosition(const int width, const int height)
{
    for(auto & i : ball_list_)
    {
        distribution_ = std::uniform_int_distribution<int>(- width/4, width/4);
        float w = distribution_(gen_);
        distribution_ = std::uniform_int_distribution<int>(- height/4, height/4);
        float h = distribution_(gen_);
        i->setPosition({width/2 + w, height/2 + h});
    }
}

void BallManager::update(float dt)
{
    //更新力（加速度）
    for (auto &i : ball_list_)
    {
        i->emptyAccel();
        for (auto &j : ball_list_)
        {
            if (i == j)
                continue;
            auto dist_vec = j->getPosition() - i->getPosition();
            float dist = dist_vec.length();
            //dist 太小不计算
            if (dist < 0.1f)
                continue;
            //使用 GM/r 的简化公式
            sf::Vector2f accel = GRAVITY * j->getMass() / dist * dist_vec.normalized();
            i->addAccel(accel);
        }
    }

    //更新位置
    for (auto &i : ball_list_)
    {
        i->update(dt);
    }
}

void BallManager::render(sf::RenderWindow &window)
{
    for (auto &i : ball_list_)
    {
        i->render(window);
    }
}


