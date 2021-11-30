#pragma once

#include "Room.hpp"
#include "Vec2.hpp"
#include "Laser.hpp"
#include "Player.hpp"
#include "Block.hpp"

class LaserBlock : public Block {
public:
    LaserBlock(Room* room, const Vec2<double>& pos, int rotate);
    void step() override;
private:
    double timer = 0;
    int laser_rotate = 0;
    Vec2<double> dpos;
};