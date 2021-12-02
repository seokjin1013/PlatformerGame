#include "Bullet.hpp"

Bullet::Bullet(const Vec2<double>& pos, int rotate) : Object(pos) {
    bullet_rotate = rotate;
    sprite_info.sprite_index = SpriteIndex::bullet;
    sprite_info.image_angle = rotate;
    if (bullet_rotate == 0) velocity = { 1.0, 0.0 };
    else if (bullet_rotate == 1) velocity = { 0.0, 1.0 };
    else if (bullet_rotate == 2) velocity = { -1.0, 0.0 };
    else if (bullet_rotate == 3) velocity = { 0.0, -1.0 };
}

void Bullet::step() {
    if (!check_box_collision<Block>(Vec2<double>{0, 0}))
        pos += velocity;
    else {
        room->del_instance(this);
        return;
    }
    if (life-- == 0) {
        room->del_instance(this);
        return;
    }
}