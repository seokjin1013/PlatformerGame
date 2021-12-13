#pragma once

#include "Room.hpp"
#include "Vec2.hpp"

class Sticker : public Object {
public:
    Sticker(const Vec2<double>& pos, SpriteIndex sprite_index, int image_index, Object* stick);
    void step() override;
private:
    Object* stick;
    Vec2<double> pos_prev;
};