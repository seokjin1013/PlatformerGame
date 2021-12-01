#pragma once

#include "Room.hpp"
#include "Vec2.hpp"
#include "Block.hpp"
#include "Laser.hpp"

class Bullet : public Object {
public:
    Bullet(const Vec2<double>& pos, int rotate);
    void step() override;
private:
    int bullet_rotate;
    int life = 10800;
    Vec2<double> velocity;
};