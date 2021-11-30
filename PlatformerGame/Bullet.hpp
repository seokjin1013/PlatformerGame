#pragma once

#include "Room.hpp"
#include "Vec2.hpp"
#include "Block.hpp"

class Bullet : public Object {
public:
    Bullet(Room* room, const Vec2<double>& pos);
    void step() override;
};