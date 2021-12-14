#pragma once

#include <cstring>
#include <numbers>
#include "Constant.hpp"
#include "Room.hpp"
#include "Utility.hpp"

class View {
public:
    View();
    virtual ~View();
    void clear();
    void draw(const Room& room);
    void draw_sprite(int* board, const Vec2<int>& size, const SpriteInfo& sprite_info, const Vec2<double>& pos);
    void draw_set_filter(int* dst, int* src, const Vec2<int>& border, double* filter_board_x, double* filter_board_y);
    void draw_time_recall_bar(int* board, const ViewInfo& view);
    void apply_filter_time_recall_effect(double strength, double period, double focus_x, double focus_y);
    void apply_information_effect(SpriteInfo information_info, double information_alpha);
    const int* get_alpha_board() const;
    const Vec2<int>& get_size() const;

private:
    int* alpha_board;
    int* alpha_board_init;
    double* filter_board_x, *filter_board_y;
    Vec2<int> size;
};
