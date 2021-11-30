#include "Laser.hpp"

Laser::Laser(Room* room, const Vec2<double>& pos, int rotate) : Object(room, pos) {
    laser_rotate = rotate;
    this->sprite_info.sprite_index = SpriteIndex::laser;
    sprite_info.image_angle = rotate;
}

void Laser::step() {
}