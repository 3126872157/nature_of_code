//
// Created by ken on 25-1-27.
//

#ifndef QUAD_TREE_H
#define QUAD_TREE_H

//std
#include <vector>
#include <memory>
#include <iostream> // for printf
#include <algorithm> // for std::remove_if

//sfml
#include "SFML/Graphics.hpp"

#define MAX_DEPTH 12
#define MAX_CAPACITY 64

template <typename T>
struct QuadTreeItem {
    sf::FloatRect rect;
    T data;
};

template <typename T>
class QuadTree {
public:
    QuadTree(const sf::FloatRect rect, const int depth);
    ~QuadTree();
    QuadTree(const QuadTree &) = delete;
    QuadTree &operator=(const QuadTree &) = delete;

public:
    void insert(QuadTreeItem<T> &data);
    void query(sf::FloatRect target, std::vector<QuadTreeItem<T>> &candidates);
    void clear();
    void draw(sf::RenderWindow &window);

private:
    int getIndex(sf::FloatRect rect) const;
    void split();

private:
    std::unique_ptr<QuadTree> children_[4] = {};
    std::vector<QuadTreeItem<T>> data_;
    sf::FloatRect bounds_;

    int capacity_;
    int depth_;

    sf::RectangleShape shape_;
};

// Implementation

template<typename T>
QuadTree<T>::QuadTree(const sf::FloatRect rect, const int depth) {
    capacity_ = 0;
    depth_ = depth;
    bounds_ = rect;
}

template <typename T>
QuadTree<T>::~QuadTree() {
    for (auto &it : children_) {
        it.reset();
    }
}

//NW: 0, NE: 1, SW: 2, SE: 3, middle: -1
template<typename T>
int QuadTree<T>::getIndex(sf::FloatRect rect) const {
    int index = -1;

    float Vertical_mid = bounds_.getCenter().x;
    float Horizontal_mid = bounds_.getCenter().y;

    bool isLeft = false;
    bool isRight = false;

    if (rect.position.x + rect.size.x < Vertical_mid) {
        isLeft = true;
    } else if (rect.position.x > Vertical_mid) {
        isRight = true;
    }

    if (rect.position.y + rect.size.y < Horizontal_mid) {
        if (isLeft) {
            index = 0;
        } else if (isRight) {
            index = 1;
        }
    } else if (rect.position.y > Horizontal_mid) {
        if (isLeft) {
            index = 2;
        } else if (isRight) {
            index = 3;
        }
    }

    return index;
}

template<typename T>
void QuadTree<T>::split() {
    auto size = bounds_.size * 0.5f;
    children_[0] = std::make_unique<QuadTree>(sf::FloatRect({bounds_.position, size}), depth_ + 1);
    children_[1] = std::make_unique<QuadTree>(sf::FloatRect({{bounds_.position.x + size.x, bounds_.position.y}, size}), depth_ + 1);
    children_[2] = std::make_unique<QuadTree>(sf::FloatRect({{bounds_.position.x, bounds_.position.y + size.y}, size}), depth_ + 1);
    children_[3] = std::make_unique<QuadTree>(sf::FloatRect({bounds_.position + size, size}), depth_ + 1);
}

template<typename T>
void QuadTree<T>::insert(QuadTreeItem<T> &data) {
    if (children_[0] != nullptr) {
        int index = getIndex(data.rect);
        if (index != -1) {
            children_[index]->insert(data);
            return;
        }
    }

    data_.emplace_back(data);

    if (data_.size() > MAX_CAPACITY && depth_ < MAX_DEPTH) {
        if (children_[0] == nullptr) {
            split();
        }

        // 优化：使用双指针法原地移除并分发元素，避免 erase 的 O(N) 开销
        auto it = data_.begin();
        while (it != data_.end()) {
            int index = getIndex(it->rect);
            if (index != -1) {
                children_[index]->insert(*it);
                // 将当前元素与最后一个元素交换，然后 pop_back
                // 注意：这会改变元素顺序，但对 QuadTree 来说顺序不重要
                std::iter_swap(it, data_.end() - 1);
                data_.pop_back();
                // 此时 it 指向了原本在末尾的元素（现在被换过来了），需要重新检查它
                // 所以这里不执行 ++it
            } else {
                ++it;
            }
        }
    }
}

template<typename T>
void QuadTree<T>::query(sf::FloatRect target, std::vector<QuadTreeItem<T>>& candidates) {
    // 检查当前节点包含的对象
    for (auto &it : data_) {
        if (target.findIntersection(it.rect)) {
            candidates.emplace_back(it);
        }
    }

    if (children_[0] != nullptr) {
        for (auto &i : children_) {
            // 递归查询子节点
            if (target.findIntersection(i->bounds_)) {
                i->query(target, candidates);
            }
        }
    }
}

template<typename T>
void QuadTree<T>::draw(sf::RenderWindow &window) {
    for (auto& it : children_) {
        if (it != nullptr) {
            it->draw(window);
        }
    }

    shape_.setPosition(bounds_.position);
    shape_.setSize(bounds_.size);
    shape_.setFillColor(sf::Color::Transparent);
    shape_.setOutlineColor(sf::Color::White);
    shape_.setOutlineThickness(0.5f);
    window.draw(shape_);
}

template<typename T>
void QuadTree<T>::clear() {
    for (auto &it : children_) {
        it.reset();
    }
    data_.clear();
}

#endif //QUAD_TREE_H