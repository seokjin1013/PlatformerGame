#pragma once

#include "Vec2.hpp"
#include "Room.hpp"
#include "Block.hpp"
#include "Player.hpp"
#include "Constant.hpp"

class BreakableBlock : public Block {
public:
    BreakableBlock(const Vec2<double>& pos);
    void step() override;

private:
    int life_max = 60;
    int life = life_max;
    bool breaking = false;
};