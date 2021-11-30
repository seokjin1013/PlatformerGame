#include "BulletShooter.hpp"

BulletShooter::BulletShooter(Room* room, const Vec2<double>& pos, int rotate) : Block(room, pos) {
    bullet_rotate = rotate;
    this->sprite_info.sprite_index = SpriteIndex::bullet_shooter;
    sprite_info.image_angle = rotate;
}

void BulletShooter::step() {
    timer += 1;
    int dx = 0;
    int dy = 0;
    if (bullet_rotate == 0) dx = 10, dy = 0;
    else if (bullet_rotate == 1) dx = 0, dy = 10;
    else if (bullet_rotate == 2) dx = -10, dy = 0;
    else if (bullet_rotate == 3) dx = 0, dy = -10;
    if (timer % 120 == 0) new Bullet(room, Vec2<double>{pos.x + dx, pos.y + dy}, bullet_rotate);
}