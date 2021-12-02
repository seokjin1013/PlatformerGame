#pragma once

#include "Room.hpp"
#include "Vec2.hpp"
#include "Block.hpp"
#include "Bullet.hpp"

class BulletBlock : public Block {
public:
    BulletBlock(const Vec2<double>& pos, int rotate);
    void step() override;
private:
    int timer = 0;
    int bullet_rotate = 0;
    Vec2<double> dpos;
};