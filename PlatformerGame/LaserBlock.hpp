#pragma once

#include "Room.hpp"
#include "Vec2.hpp"
#include "Player.hpp"
#include "Block.hpp"

class LaserBlock : public Block {
public:
    LaserBlock(const Vec2<double>& pos, int rotate);
    void step() override;
private:
    bool create = false;
    double timer = 0;
    int rotate = 0;
    Vec2<double> dpos;
    int laser_thinness = 4;
    double laser_range_max = 30;
    double laser_range = laser_range_max;
};