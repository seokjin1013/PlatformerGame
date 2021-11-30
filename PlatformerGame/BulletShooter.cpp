#include "BulletShooter.hpp"

BulletShooter::BulletShooter(Room* room, const Vec2<double>& pos, int rotate) : Block(room, pos) {
    bullet_rotate = rotate;
    this->sprite_info.sprite_index = SpriteIndex::bullet_shooter;
    sprite_info.image_angle = rotate;
    if (rotate == 0) dpos = { 10, 0 };
    else if (rotate == 1) dpos = { 0, 10 };
    else if (rotate == 2) dpos = { -10, 0 };
    else if (rotate == 3) dpos = { 0, -10 };
}

void BulletShooter::step() {
    if (timer++ >= 120) {
        new Bullet(room, pos + dpos, bullet_rotate);
        timer = 0;
    }
}