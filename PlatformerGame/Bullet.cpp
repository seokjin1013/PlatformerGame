#include "Bullet.hpp"

Bullet::Bullet(Room* room, const Vec2<double>& pos) : Object(room, pos) {
    this->sprite_info.sprite_index = SpriteIndex::bullet;
}

void Bullet::step() {
    if(!check_box_collision<Block>(Vec2<double>{0,0}))pos += {1, 0};
    else { this->~Bullet(); }
}