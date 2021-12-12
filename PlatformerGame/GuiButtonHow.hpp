#pragma once

#include "GuiButton.hpp"

class GuiButtonHow : public GuiButton {
public:
    GuiButtonHow(const Vec2<double>& pos);
    void step();
    void trigger();
    void focus();
    void unfocus();
private:
    bool is_trigger = false;
    bool is_focus = false;
};