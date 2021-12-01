#pragma once

#include "Room.hpp"
#include "Vec2.hpp"
#include "Player.hpp"

class Goal : public Object {
public:
    Goal(const Vec2<double>& pos, int next_room);
    void step() override;
private:
    int next_room;
};