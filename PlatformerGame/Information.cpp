#include "Information.hpp"

Information::Information(const Vec2<double>& pos, SpriteInfo information_sprite) : Object(pos) {
    sprite_info.sprite_index = SpriteIndex::information;
    this->information_sprite = information_sprite;
}

void Information::step() {
    if (check_box_collision<Player>({ 0, 0 }))
        room->view_info.information_sprite = information_sprite;
}