#pragma once

#include <cstring>
#include "Constant.hpp"
#include "Room.hpp"
#include "Utility.hpp"

class View {
public:
    View();
    virtual ~View();
    void clear();
    void draw(const Room& room);
    void smooth_rendering(const SpriteInfo& sprite_info, const Vec2<double>& pos);
    void clear_rendering(const SpriteInfo& sprite_info, const Vec2<double>& pos);
    void clear_rendering2(const SpriteInfo& sprite_info, const Vec2<double>& pos);
    const int* get_alpha_board() const;
    const Vec2<int>& get_size() const;

private:
    int* alpha_board;
    Vec2<int> size;
};
