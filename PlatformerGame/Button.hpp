#pragma once

#include "Room.hpp"
#include "Vec2.hpp"

class Button : public Object {
public:
    Button(Room* room, const Vec2<double>& pos);
    void step() override;
};