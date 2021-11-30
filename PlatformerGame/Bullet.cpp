#include "Bullet.hpp"

Bullet::Bullet(Room* room, const Vec2<double>& pos, int rotate) : Object(room, pos) {
    bullet_rotate = rotate;
    this->sprite_info.sprite_index = SpriteIndex::bullet;
    sprite_info.image_angle = rotate;
}

void Bullet::step() {
    double dx = 0.0;
    double dy = 0.0;
    if (bullet_rotate == 0) dx = 1.0, dy = 0.0;
    else if (bullet_rotate == 1) dx = 0.0, dy = 1.0;
    else if (bullet_rotate == 2) dx = -1.0, dy = 0.0;
    else if (bullet_rotate == 3) dx = 0.0, dy = -1.0;
    if (!check_box_collision<Block>(Vec2<double>{0, 0})) pos += { dx, dy };
    else delete this;
}