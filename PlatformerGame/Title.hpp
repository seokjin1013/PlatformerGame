#pragma once

#include "Room.hpp"
#include "Vec2.hpp"

class Title : public Object {
public:
    Title(Room* room, const Vec2<double>& pos);
    void step() override;
};