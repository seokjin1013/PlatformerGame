#pragma once

#include <numbers>
#include "Room.hpp"
#include "Vec2.hpp"
#include "utility.hpp"

class GuiButton : public Object {
public:
    GuiButton(const Vec2<double>& pos, SpriteIndex sprite_index);
    void step();
    void trigger();
    void denied();
    void focus();
    void unfocus();
    bool is_trigger_start = false;
    bool is_trigger_end = false;
    bool is_focus = false;
    bool is_denied = false;
private:
    int trigger_motion_index = 0;
    int trigger_motion_index_max = 30;
    int denied_motion_index = 0;
    int denied_motion_index_max = 30;
    int focus_effect_index = 0;
    int focus_effect_index_max = 15;
    Vec2<double> original_pos;
};