#include "Goal.hpp"

Goal::Goal(Room* room, const Vec2<double>& pos, int next_room) : Object(room, pos) {
    this->sprite_info.sprite_index = SpriteIndex::goal;
    this->next_room = next_room;
}

void Goal::step() {
    if (room->key_flag == 1) {
        if (check_box_collision<Player>({ 0, 0 })) {
            PlayManager::instance().set_room(next_room);
        }
    }
}