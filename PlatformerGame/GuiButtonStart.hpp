#pragma once

#include "GuiButton.hpp"

class GuiButtonStart : public GuiButton {
public:
    GuiButtonStart(const Vec2<double>& pos);
    void step();
    void trigger();
    void focus();
    void unfocus();
private:
    bool is_trigger = false;
    bool is_focus = false;
};