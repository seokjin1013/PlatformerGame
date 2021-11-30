#pragma once

#include "Room.hpp"
#include "Vec2.hpp"
#include "Player.hpp"

class Battery : public Object {
public:
    Battery(Room* room, const Vec2<double>& pos);
    void step() override;
};