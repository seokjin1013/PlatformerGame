#include "Goal.hpp"

Goal::Goal(const Vec2<double>& pos, RoomIndex next_room) : Object(pos) {
    sprite_info.sprite_index = SpriteIndex::goal;
    this->next_room = next_room;
}

void Goal::step() {
    if (room->key_flag == 1) {
        if (check_box_collision<Player>({ 0, 0 })) {
            PlayManager::instance().set_room(next_room);
        }
    }
}