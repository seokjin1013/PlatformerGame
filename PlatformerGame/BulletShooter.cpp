#include "BulletShooter.hpp"

BulletShooter::BulletShooter(Room* room, const Vec2<double>& pos) : Object(room, pos) {
    this->sprite_info.sprite_index = SpriteIndex::bullet_shooter;
}

void BulletShooter::step() {
    timer += 1;
    if (timer % 120 == 0) new Bullet(room, Vec2<double>{ pos.x + 10, pos.y });
}