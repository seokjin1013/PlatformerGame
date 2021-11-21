#pragma once

#include "Object.hpp"
#include "Vec2.hpp"
#include "Player.hpp"

class Goal : public Object {
public:
    Goal(Room* room, const Vec2<double>& pos, int next_room);
    void step() override;
    template <typename T>
    bool check_box_collision(const Vec2<double>& velocity);
private:
    int next_room;
};