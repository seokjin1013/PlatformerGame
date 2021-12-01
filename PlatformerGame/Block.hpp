#pragma once

#include "Room.hpp"
#include "Vec2.hpp"

class Block : public Object {
public:
    Block(const Vec2<double>& pos);
    void step() override;
};