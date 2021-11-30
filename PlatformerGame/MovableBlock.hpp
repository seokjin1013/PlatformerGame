#pragma once

#include "Vec2.hpp"
#include "Room.hpp"
#include "Block.hpp"

class MovableBlock : public Block {
public:
    MovableBlock(Room* room, const Vec2<double>& pos);
    void step() override;

private:
    Vec2<double> velocity = {0, 0};
    double gravity = 0.05;
};