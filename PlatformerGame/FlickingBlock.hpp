#pragma once

#include "Room.hpp"
#include "Vec2.hpp"
#include "Block.hpp"
#include "Controller.hpp"
#include "Player.hpp"

class FlickingBlockOn : public Block {
public:
    FlickingBlockOn(const Vec2<double>& pos);
    void step() override;
    void toggle();
};

class FlickingBlockOff : public Object {
public:
    FlickingBlockOff(const Vec2<double>& pos);
    void step() override;
    void toggle();
};