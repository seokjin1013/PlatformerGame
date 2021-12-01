#include "BulletShooter.hpp"

BulletShooter::BulletShooter(const Vec2<double>& pos, int rotate) : Block(pos) {
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
        room->add_instance(new Bullet(pos + dpos, bullet_rotate));
        timer = 0;
    }
}