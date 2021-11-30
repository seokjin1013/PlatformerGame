#pragma once

#include "Player.hpp"
#include "Room.hpp"
#include "Vec2.hpp"

class Key : public Object {
public:
    Key(Room* room, const Vec2<double>& pos);
    void step() override;
};