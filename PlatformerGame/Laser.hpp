#pragma once

#include "Room.hpp"
#include "Vec2.hpp"
#include "Block.hpp"

class Laser : public Object {
public:
    Laser(Room* room, const Vec2<double>& pos, int rotate);
    void step() override;
private:
    int laser_rotate;
};