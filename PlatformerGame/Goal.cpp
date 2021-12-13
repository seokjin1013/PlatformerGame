#include "Goal.hpp"

Goal::Goal(const Vec2<double>& pos, RoomIndex next_room) : Object(pos) {
    sprite_info.sprite_index = SpriteIndex::goal;
    this->next_room = next_room;
}

void Goal::step() {
    if (room->key_flag == 1 && !cleared) {
        for (Object* e : room->get_pool()) {
            if (Player* p = dynamic_cast<Player*>(e)) {
                if (is_box_collide({ 0, 0 }, p)) {
                    cleared = true;
                    int current_room = static_cast<int>(PlayManager::instance().get_room()) - static_cast<int>(RoomIndex::stage1);
                    if (PlayManager::instance().star_count[current_room] < p->battery_count + 1) {
                        PlayManager::instance().star_count[current_room] = p->battery_count + 1;
                        PlayManager::instance().save_data();
                    }
                    PlayManager::instance().set_room(next_room);
                }
            }
        }
    }
}