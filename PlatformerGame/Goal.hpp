#pragma once

#include "Room.hpp"
#include "Vec2.hpp"
#include "Player.hpp"

class Goal : public Object {
public:
    Goal(const Vec2<double>& pos, RoomIndex next_room);
    void step() override;
private:
    RoomIndex next_room;
    bool cleared = false;
};