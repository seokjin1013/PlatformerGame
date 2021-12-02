#include "ButtonBlock.hpp"

ButtonBlockOn::ButtonBlockOn(const Vec2<double>& pos) : Block(pos) {
    sprite_info.sprite_index = SpriteIndex::button_block;
    sprite_info.image_index = 0;
}

void ButtonBlockOn::step() {
}

void ButtonBlockOn::toggle() {
    room->add_instance(new ButtonBlockOff(pos));
    room->del_instance(this);
}

ButtonBlockOff::ButtonBlockOff(const Vec2<double>& pos) : Object(pos) {
    sprite_info.sprite_index = SpriteIndex::button_block;
    sprite_info.image_index = 1;
}

void ButtonBlockOff::step() {
}

void ButtonBlockOff::toggle() {
    auto pool = room->get_pool();
    for (auto& e : pool) {
        if (is_box_collide({ 0, 0 }, e)) {
            room->del_instance(e);
        }
    }
    room->del_instance(this);
    room->add_instance(new ButtonBlockOn(pos));
}