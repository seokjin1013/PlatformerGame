#pragma once

#include "Room.hpp"
#include "Vec2.hpp"
#include "Controller.hpp"
#include "PlayManager.hpp"
#include "GuiButton.hpp"
#include "Sticker.hpp"

class StageSelection : public Object {
public:
    StageSelection(const Vec2<double>& pos);
    void step() override;
private:
    int focus = 0;
    bool level_button_create = false;
    bool selected = false;
    GuiButton* stage[20];
};