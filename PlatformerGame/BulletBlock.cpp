#include "BulletBlock.hpp"

BulletBlock::BulletBlock(const Vec2<double>& pos, int rotate) : Block(pos) {
    bullet_rotate = rotate;
    sprite_info.sprite_index = SpriteIndex::bullet_block;
    sprite_info.image_angle = rotate;
    if (rotate == 0) dpos = { 10, 0 };
    else if (rotate == 1) dpos = { 0, 10 };
    else if (rotate == 2) dpos = { -10, 0 };
    else if (rotate == 3) dpos = { 0, -10 };
}

void BulletBlock::step() {
    if (timer++ >= 120) {
        room->add_instance(new Bullet(pos + dpos, bullet_rotate));
        timer = 0;
    }
}