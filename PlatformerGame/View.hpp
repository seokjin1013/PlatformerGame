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
    void draw_set_filter(int* dst, int* src, const Vec2<int>& border, Vec2<double>* filter_board);
    void draw_time_recall_bar(int* board, const ViewInfo& view);
    void apply_filter_time_recall_effect(double strength, double period);
    const int* get_alpha_board() const;
    const Vec2<int>& get_size() const;

private:
    int* alpha_board;
    int* alpha_board_init;
    Vec2<double>* filter_board;
    Vec2<int> size;
};
