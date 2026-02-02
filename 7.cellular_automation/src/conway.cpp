//
// Created by ken on 26-1-29.
//

#include "../include/conway.h"
#include <random> // 引入随机数库

sf::Vector2i Conway::wrap(const sf::Vector2i in) const
{
    sf::Vector2i out = in;
    // 使用 grid_size_ (网格数量) 而不是 window_size_ (像素)
    int w = static_cast<int>(grid_size_.x);
    int h = static_cast<int>(grid_size_.y);

    if (in.x < 0) out.x = w - 1;
    else if (in.x >= w) out.x = 0;

    if (in.y < 0) out.y = h - 1;
    else if (in.y >= h) out.y = 0;

    return out;
}

void Conway::applyRule(const int x, const int y)
{
    int alive_sum = 0;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0) continue;
            sf::Vector2i t = wrap({x + i, y + j});
            alive_sum += state_[t.y][t.x];
        }
    }

    // 双缓冲，所以这里是无遗漏的覆盖式更新
    if (state_[y][x] == 1)
    {
        new_state_[y][x] = (alive_sum == 2 || alive_sum == 3) ? 1 : 0;
    }
    else
    {
        new_state_[y][x] = (alive_sum == 3) ? 1 : 0;
    }
}

Conway::Conway(const sf::RenderWindow& window)
{
    auto win_size = window.getSize();
    grid_size_.x = win_size.x / SIZE;
    grid_size_.y = win_size.y / SIZE;

    state_.assign(grid_size_.y, std::vector<int>(grid_size_.x, 0));
    new_state_.assign(grid_size_.y, std::vector<int>(grid_size_.x, 0));

    generation_ = 0;
    clear_flag_ = false;
    run_flag_ = false; // 初始设为 false 方便查看文字

    initDrawUI();

    vertices_.setPrimitiveType(sf::PrimitiveType::Triangles);
}

void Conway::write(sf::Vector2i pos, int state)
{
    // 简单的边界检查防止崩溃
    if (pos.x >= 0 && pos.x < grid_size_.x && pos.y >= 0 && pos.y < grid_size_.y)
    {
        state_[pos.y][pos.x] = state;
        new_state_[pos.y][pos.x] = state;
    }
}

// 我们定义一个 Lambda 函数来方便绘制字符
void Conway::drawChar(int startX, int startY, const std::vector<std::string>& mask)
{
    for (int row = 0; row < mask.size(); ++row)
    {
        for (int col = 0; col < mask[row].size(); ++col)
        {
            if (mask[row][col] == '#')
            {
                write({startX + col, startY + row}, 1);
            }
        }
    }
}

void Conway::initDrawUI()
{

    int offset_x = 3;
    int offset_y = 3;
    int ch_y = 7;

    // MOUSE: DRAW
    drawChar(offset_x, offset_y + ch_y * 0, {
                 "#   #  ##  #  # ### ####     ###  ###   ##  #   #",
                 "## ## #  # #  # #   #        #  # #  # #  # #   #",
                 "# # # #  # #  # ### ###   #  #  # ###  #### # # #",
                 "#   # #  # #  #   # #        #  # #  # #  # # # #",
                 "#   #  ##   ##  ### ####  #  ###  #  # #  #  # # "
             });

    // KEY-C: CLEAR
    drawChar(offset_x, offset_y + ch_y * 1, {
                 "#  # ### #   #       ###      ### #    ####  ##  ### ",
                 "# #  #    # #       #        #    #    #    #  # #  #",
                 "##   ###   #        #     #  #    #    ###  #### ### ",
                 "# #  #     #        #        #    #    #    #  # #  #",
                 "#  # ###   #         ###  #   ### #### #### #  # #  #"
             });

    drawChar(offset_x, offset_y + ch_y * 3, {
                 "#### ###   ##   ### ####     ###  #  # #  #    #  #### #####  ##  ### ",
                 "#    #  # #  # #    #        #  # #  # ## #    #  #      #   #  # #  #",
                 "#### ###  #### #    ###   #  ###  #  # ## #   #   ####   #   #  # ### ",
                 "   # #    #  # #    #        #  # #  # # ##  #       #   #   #  # #   ",
                 "#### #    #  #  ### ####  #  #  #  ##  #  #  #    ####   #    ##  #   "
             });

    drawChar(offset_x, offset_y + ch_y * 2, {
                 "#  # ### #   #      ###      ###   ##  #  # ###   ##  #   #",
                 "# #  #    # #       #  #     #  # #  # ## # #  # #  # ## ##",
                 "##   ###   #        ###   #  ###  #### ## # #  # #  # # # #",
                 "# #  #     #        #  #     #  # #  # # ## #  # #  # #   #",
                 "#  # ###   #        #  #  #  #  # #  # #  # ###   ##  #   #"
             });

    drawChar(offset_x, offset_y + ch_y * 4, {
                 "               #  # ###      ####  ##  #### #####",
                 "               #  # #  #     #    #  # #      #  ",
                 "               #  # ###   #  #### #### ####   #  ",
                 "               #  # #        #    #  #    #   #  ",
                 "                ##  #     #  #    #  # ####   #  "
             });

    drawChar(offset_x, offset_y + ch_y * 5, {
                 "    ###   ##  #   # #  #     #### #     ##  #   #",
                 "    #  # #  # #   # ## #     #    #    #  # #   #",
                 "    #  # #  # # # # ## #  #  #### #    #  # # # #",
                 "    #  # #  # # # # # ##        # #    #  # ## ##",
                 "    ###   ##   # #  #  #  #  #### ####  ##   # # "
             });

    // 绘制 "BY:Liangjun"
    drawChar(offset_x + 55, offset_y + ch_y * 8, {
                 "               ###  #   #    #   ###  ##  #  #  ###  ### #  # #  #",
                 "               #  #  # #     #    #  #  # ## # #      #  #  # ## #",
                 "               ###    #   #  #    #  #### ## # # ##   #  #  # ## #",
                 "               #  #   #      #    #  #  # # ## #  #   #  #  # # ##",
                 "               ###    #   #  ### ### #  # #  #  ###  ##   ##  #  #"
             });
}

void Conway::randomInit()
{
    // 1. 随机数引擎 (Engine)
    // std::random_device 用于获取一个非确定性的随机种子（通常来自硬件熵）
    std::random_device rd;
    // std::mt19937 是梅森旋转算法 (Mersenne Twister)，是目前最常用的高质量伪随机数生成器
    std::mt19937 gen(rd());

    // 2. 分布 (Distribution)
    // 我们想要一个 0 到 100 之间的均匀整数分布
    std::uniform_int_distribution<> dis(0, 100);

    for (int y = 0; y < grid_size_.y; ++y)
    {
        for (int x = 0; x < grid_size_.x; ++x)
        {
            // 3. 生成随机数
            // 调用 dis(gen) 会使用 gen 引擎生成一个符合 dis 分布的随机数
            if (dis(gen) < 20)
            {
                // 20% 概率存活
                write({x, y}, 1);
            }
        }
    }
}

void Conway::update(float dt)
{
    if (clear_flag_)
        clear();

    if (!run_flag_)
        return;

    // 控制帧率
    static float time = 0;
    time += dt;
    if (time <= t_max)
    {
        return;
    }
    time = 0;

    for (int j = 0; j < grid_size_.y; j++)
    {
        for (int i = 0; i < grid_size_.x; i++)
        {
            applyRule(i, j);
        }
    }
    state_.swap(new_state_);
}

void Conway::render(sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        draw(sf::Mouse::getPosition(window));
    }

    vertices_.clear();

    for (int j = 0; j < grid_size_.y; j++)
    {
        for (int i = 0; i < grid_size_.x; i++)
        {
            if (state_[j][i] == 1)
            {
                float x = static_cast<float>(i * SIZE);
                float y = static_cast<float>(j * SIZE);

                // 构造两个三角形组成一个矩形
                // p1 --- p2
                // |       |
                // p4 --- p3

                sf::Vector2f p1(x, y);
                sf::Vector2f p2(x + SIZE, y);
                sf::Vector2f p3(x + SIZE, y + SIZE);
                sf::Vector2f p4(x, y + SIZE);

                sf::Color color = sf::Color::White;

                // Triangle 1
                vertices_.append(sf::Vertex{p1, color});
                vertices_.append(sf::Vertex{p2, color});
                vertices_.append(sf::Vertex{p3, color});

                // Triangle 2
                vertices_.append(sf::Vertex{p3, color});
                vertices_.append(sf::Vertex{p4, color});
                vertices_.append(sf::Vertex{p1, color});
            }
        }
    }

    window.draw(vertices_);
}

void Conway::setClearFlag()
{
    clear_flag_ = true;
}

void Conway::clear()
{
    for (int i = 0; i < state_.size(); i++)
    {
        std::fill(state_[i].begin(), state_[i].end(), 0);
        std::fill(new_state_[i].begin(), new_state_[i].end(), 0);
    }
    clear_flag_ = false;
}

void Conway::toggleRunFlag()
{
    run_flag_ = !run_flag_;
}

void Conway::draw(sf::Vector2i mouse_pos)
{
    static sf::Vector2i last_pos = {0, 0};
    sf::Vector2i pos = {mouse_pos.x / SIZE, mouse_pos.y / SIZE};

    if (pos == last_pos)
        return;

    //翻转细胞状态
    state_[pos.y][pos.x] = state_[pos.y][pos.x] == 1 ? 0 : 1;

    last_pos = pos;
}

void Conway::changeFrameRate(bool is_up)
{
    if (is_up)
    {
        t_max = std::max(0.0167f, t_max - 0.1f);
    }
    else
    {
        t_max = std::min(1.0f, t_max + 0.1f);
    }
}
