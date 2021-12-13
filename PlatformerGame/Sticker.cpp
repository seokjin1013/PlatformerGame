#include "Sticker.hpp"

Sticker::Sticker(const Vec2<double>& pos, SpriteIndex sprite_index, int image_index, Object* stick) : Object(pos) {
    sprite_info.sprite_index = sprite_index;
    sprite_info.image_index = image_index;
    this->stick = stick;
    pos_prev = stick->get_pos();
}

void Sticker::step() {
    pos += stick->get_pos() - pos_prev;
    pos_prev = stick->get_pos();
}