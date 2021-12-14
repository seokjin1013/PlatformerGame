#include "Follower.hpp"

Follower::Follower(const Vec2<double>& pos, SpriteIndex sprite_index, int image_index, Object* target) : Object(pos) {
    sprite_info.sprite_index = sprite_index;
    sprite_info.image_index = image_index;
    this->target = target;
    this->target_pos = target->get_pos();
}

void Follower::set_target(Object* target) {
    this->target = target;
}

void Follower::step() {
    if (target != nullptr) {
        target_pos = target->get_pos();
        if (double dist = (pos - target_pos).norm(); dist > 5)
            target_pos += (pos - target_pos) / dist * 5;
    }
    pos = utility::lerp(pos, target_pos, 0.1);
}