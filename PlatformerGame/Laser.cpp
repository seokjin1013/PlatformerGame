#include "Laser.hpp"

Laser::Laser(const Vec2<double>& pos, int rotate) : Object(pos) {
    laser_rotate = rotate;
    sprite_info.sprite_index = SpriteIndex::laser;
    sprite_info.image_angle = rotate;
}

void Laser::step() {
}