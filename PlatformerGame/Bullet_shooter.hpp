#pragma once

#include "Object.hpp"
#include "Vec2.hpp"
#include "Bullet.hpp"


class Bullet_shooter : public Object {
public:
    int timer = 0;
    Bullet_shooter(Room* room, const Vec2<double>& pos);
    void step() override;
};