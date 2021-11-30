#pragma once

#include "Room.hpp"
#include "Vec2.hpp"
#include "Bullet.hpp"

class BulletShooter : public Object {
public:
    int timer = 0;
    BulletShooter(Room* room, const Vec2<double>& pos);
    void step() override;
};