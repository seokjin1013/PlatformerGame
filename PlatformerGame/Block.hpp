#pragma once

#include "Object.hpp"
#include "Vec2.hpp"

class Block : public Object {
public:
    Block(Room* room, const Vec2<double>& pos);
    void step() override;
};