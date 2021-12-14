#pragma once

#include "Room.hpp"
#include "Vec2.hpp"

class Sticker : public Object {
public:
    Sticker(const Vec2<double>& pos, SpriteIndex sprite_index, int image_index, Object* target);
    void step() override;
    void set_image_index(int image_index);
private:
    Object* target;
    Vec2<double> pos_prev;
};