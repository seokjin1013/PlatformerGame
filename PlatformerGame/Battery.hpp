#pragma once

#include "Room.hpp"
#include "Vec2.hpp"
#include "Player.hpp"

class Battery : public Object {
public:
    Battery(const Vec2<double>& pos);
    void step() override;
};