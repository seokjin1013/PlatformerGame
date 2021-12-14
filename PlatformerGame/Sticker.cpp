#include "Sticker.hpp"

Sticker::Sticker(const Vec2<double>& pos, SpriteIndex sprite_index, int image_index, Object* target) : Object(pos) {
    sprite_info.sprite_index = sprite_index;
    sprite_info.image_index = image_index;
    this->target = target;
    pos_prev = target->get_pos();
}

void Sticker::set_image_index(int image_index) {
    sprite_info.image_index = image_index;
}

void Sticker::step() {
    pos += target->get_pos() - pos_prev;
    pos_prev = target->get_pos();
}