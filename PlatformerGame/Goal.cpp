#include "Goal.hpp"

Goal::Goal(Room* room, const Vec2<double>& pos, int next_room) : Object(room, pos) {
    this->sprite_info.sprite_index = SpriteIndex::goal;
    this->next_room = next_room;
}

template <typename T>
bool Goal::check_box_collision(const Vec2<double>& velocity) {
    auto pool = room->get_pool();
    auto pos0 = pos;
    auto pos1 = pos + velocity;
    pos = pos1;
    for (const auto e : pool) {
        if (e == this) continue;
        if (T* p = dynamic_cast<T*>(e)) {
            if (is_box_collide(e)) {
                pos = pos0;
                return true;
            }
        }
    }
    pos = pos0;
    return false;
}

void Goal::step() {
    if (room->key_flag == 1) {
        if (check_box_collision<Player>({ 0, 0 })) {
            PlayManager::instance().set_room(next_room);
        }
    }
}