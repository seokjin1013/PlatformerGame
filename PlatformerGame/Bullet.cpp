#include "Bullet.hpp"

Bullet::Bullet(Room* room, const Vec2<double>& pos, int rotate) : Object(room, pos) {
    bullet_rotate = rotate;
    this->sprite_info.sprite_index = SpriteIndex::bullet;
    sprite_info.image_angle = rotate;
    if (bullet_rotate == 0) velocity = { 1.0, 0.0 };
    else if (bullet_rotate == 1) velocity = { 0.0, 1.0 };
    else if (bullet_rotate == 2) velocity = { -1.0, 0.0 };
    else if (bullet_rotate == 3) velocity = { 0.0, -1.0 };
}

void Bullet::step() {
    if (!check_box_collision<Block>(Vec2<double>{0, 0}) && !check_box_collision<Laser>(Vec2<double>{0, 0}))
        pos += velocity;
    else
        delete this;
    if (life-- == 0)
        delete this;
}