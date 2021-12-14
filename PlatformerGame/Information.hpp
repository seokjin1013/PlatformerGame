#pragma once

#include "Room.hpp"
#include "Vec2.hpp"
#include "Player.hpp"

class Information : public Object {
public:
    Information(const Vec2<double>& pos, SpriteInfo information_sprite);
    void step() override;
private:
    SpriteInfo information_sprite;
};