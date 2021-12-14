#pragma once

#include "Room.hpp"
#include "Vec2.hpp"
#include "Utility.hpp"

class Follower : public Object {
public:
    Follower(const Vec2<double>& pos, SpriteIndex sprite_index, int image_index, Object* target);
    void step() override;
    void set_target(Object* target);
private:
    Object* target;
    Vec2<double> target_pos;
};