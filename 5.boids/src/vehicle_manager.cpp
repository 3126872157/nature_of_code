//
// Created by ken on 25-7-20.
//

#include "../include/vehicle_manager.h"

VehicleManager::VehicleManager(const int num, sf::Vector2f window) : qt_root_(QuadTree<Vehicle*>(sf::FloatRect({0, 0}, window), 0)){
    num_ = num;
    separation_ = 45.0;
    coherence_ = 75.0;
    alignment_ = 105.0;

    // 预分配内存，减少动态扩容
    list_.reserve(num);
    candidates_.reserve(100); // 假设每个boid周围最多有100个邻居

    for (int i = 0; i < num; i++) {
        list_.emplace_back(new Vehicle());
        list_.back()->setPosition({rand() * window.x / RAND_MAX, rand() * window.y / RAND_MAX});
        float angle = 2.0f * M_PI * rand() / RAND_MAX;
        float speed = rand() % 100 + 50;
        list_.back()->setVelocity({speed * cosf(angle), speed * sinf(angle)});

        qt_item_.rect = sf::FloatRect(list_.back()->getPosition(), {1, 1});
        qt_item_.data = list_.back();
        qt_root_.insert(qt_item_);
    }
}

void VehicleManager::update(float dt) {
    static float t;
    t += dt;

    // 1. 计算群聚力 (合并了 separate, align, cohere)
    applyFlocking(t);

    // 2. 重建四叉树
    // 优化：如果物体移动不剧烈，可以考虑隔几帧重建一次，或者只更新移动了的物体
    // 但目前全量重建是最安全的
    qt_root_.clear();

    for (auto &vehicle: list_) {
        // 3. 更新物理状态
        vehicle->update(dt);

        // 插入四叉树
        qt_item_.rect.position = vehicle->getPosition();
        qt_item_.data = vehicle;
        qt_root_.insert(qt_item_);
    }
}

void VehicleManager::applyFlocking(float t) {
    // 使用最大的感知半径进行查询
    float max_dist = std::max({separation_, coherence_, alignment_});
    auto size = sf::Vector2f(max_dist * 2, max_dist * 2);
    auto range = sf::FloatRect({0, 0}, size);

    // 预计算平方距离，避免开方
    float sep_sq = separation_ * separation_;
    float coh_sq = coherence_ * coherence_;
    float ali_sq = alignment_ * alignment_;

    for (auto &myself: list_) {
        sf::Vector2f sep_sum = {};
        sf::Vector2f ali_sum = {};
        sf::Vector2f coh_sum = {};

        int sep_count = 0;
        int ali_count = 0;
        int coh_count = 0;

        range.position = myself->getPosition() - size * 0.5f;
        candidates_.clear();
        qt_root_.query(range, candidates_);

        for (auto &it: candidates_) {
            auto other = it.data;
            if (myself != other) {
                auto dist_vec = myself->getPosition() - other->getPosition();
                float d_sq = dist_vec.lengthSquared(); // 使用平方长度

                // Separation
                if (d_sq < sep_sq && d_sq > 0) {
                    // 这里的 dist_vec 是 myself - other (指向自己，排斥)
                    // 原始逻辑: sum += dist.normalized() / d;
                    // 优化: dist.normalized() / d = (dist / d) / d = dist / d^2
                    sep_sum += dist_vec / d_sq;
                    sep_count++;
                }

                // Alignment
                if (d_sq < ali_sq) {
                    // 原始逻辑包含了一个 dot product 检查，这里为了性能先简化，或者你可以加回来
                    // if (dist.dot(my_vel) ... )
                    ali_sum += other->getVelocity();
                    ali_count++;
                }

                // Cohesion
                if (d_sq < coh_sq && d_sq > 0) {
                    // 累加绝对位置
                    coh_sum += other->getPosition();
                    coh_count++;
                }
            }
        }

        // Apply Separation
        if (sep_count > 0) {
            sep_sum /= static_cast<float>(sep_count);
            if (sep_sum.lengthSquared() > 0) { // 检查平方长度是否大于0
                sep_sum = sep_sum.normalized();
                myself->steer(sep_sum, getSin(3, 5, 1, t));
            }
        }

        // Apply Alignment
        if (ali_count > 0) {
            ali_sum /= static_cast<float>(ali_count);
            if (ali_sum.lengthSquared() > 0) {
                ali_sum = ali_sum.normalized();
                myself->steer(ali_sum, getSin(1, 2, 1, t));
            }
        }

        // Apply Cohesion
        if (coh_count > 0) {
            coh_sum /= static_cast<float>(coh_count);
            myself->seek(coh_sum, getSin(0.4, 0.5, 1, t)); // 注意 seek 内部实现是否高效
        }
    }
}

void VehicleManager::seek(sf::Vector2f target) {
    for (const auto &vehicle: list_) {
        vehicle->seek(target, 0.3f); // 假设 Vehicle::seek 支持第二个参数
    }
}


void VehicleManager::render(sf::RenderWindow &window) {
    for (const auto &vehicle: list_) {
        vehicle->render(window);
        // qt_root_.draw(window);
    }
}
