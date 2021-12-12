#pragma once

#include "GuiButton.hpp"

class GuiButtonExit : public GuiButton {
public:
    GuiButtonExit(const Vec2<double>& pos);
    void step();
    void trigger();
    void focus();
    void unfocus();
private:
    bool is_trigger = false;
    bool is_focus = false;
};