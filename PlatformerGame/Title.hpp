#pragma once

#include "Room.hpp"
#include "Vec2.hpp"
#include "Controller.hpp"
#include "PlayManager.hpp"
#include "GuiButton.hpp"
#include "Sticker.hpp"

class Title : public Object {
public:
    Title(const Vec2<double>& pos);
    void step() override;
private:
    GuiButton* menu[3];
    bool press = false;
    bool selected = false;
    int focus = 0;
    int flicking_text_delay = 0;
    int flicking_text_delay_max = 30;
};