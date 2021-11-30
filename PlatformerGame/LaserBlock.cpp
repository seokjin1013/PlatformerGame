#include "LaserBlock.hpp"

LaserBlock::LaserBlock(Room* room, const Vec2<double>& pos, int rotate) : Block(room, pos) {
    laser_rotate = rotate;
    this->sprite_info.sprite_index = SpriteIndex::laser_block;
    sprite_info.image_angle = rotate;
    if (rotate == 0) dpos = { 10, 0 };
    else if (rotate == 1) dpos = { 0, 10 };
    else if (rotate == 2) dpos = { -10, 0 };
    else if (rotate == 3) dpos = { 0, -10 };

    while (!check_box_collision<Block>(dpos * ++timer) && timer < 100)
        new Laser(room, pos + dpos * timer, laser_rotate);
}

void LaserBlock::step() {
}