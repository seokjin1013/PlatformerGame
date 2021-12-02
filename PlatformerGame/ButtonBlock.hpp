#pragma once

#include "Room.hpp"
#include "Vec2.hpp"
#include "Block.hpp"

class ButtonBlockOn : public Block {
public:
    ButtonBlockOn(const Vec2<double>& pos);
    void step() override;
    void toggle();
};

class ButtonBlockOff : public Object {
public:
    ButtonBlockOff(const Vec2<double>& pos);
    void step() override;
    void toggle();
};