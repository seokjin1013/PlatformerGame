#pragma once

#include "Room.hpp"
#include "Vec2.hpp"
#include "Player.hpp"
#include "ButtonBlock.hpp"

class Button : public Object {
public:
    Button(const Vec2<double>& pos, bool is_on);
    void step() override;
private:
    void toggle();
    bool collide_with_player = false;
    bool is_on = false;
};