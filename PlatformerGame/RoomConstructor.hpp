#pragma once

#include "Room.hpp"
#include "Vec2.hpp"
#include "Player.hpp"

class RoomConstructor : public Object {
public:
    RoomConstructor(const Vec2<double>& pos, RoomIndex current_room);
    void step();
private:
    RoomIndex current_room;
};