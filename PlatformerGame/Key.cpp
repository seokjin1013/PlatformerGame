#include "Key.hpp"

Key::Key(const Vec2<double>& pos) : Object(pos) {
    this->sprite_info.sprite_index = SpriteIndex::key;
}

void Key::step() {
    if (check_box_collision<Player>(Vec2<double>{0, 0})) {
        room->key_flag = 1;
        room->del_instance(this);
    }
}