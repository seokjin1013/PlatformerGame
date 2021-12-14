#include "Particle.hpp"

Particle::Particle(const Vec2<double>& pos, SpriteIndex sprite_index, int life_max) : Object(pos) {
    sprite_info.sprite_index = sprite_index;
    sprite_info.image_index = 0;
    this->life_max = life_max;
}

void Particle::step() {
    sprite_info.image_index = utility::lerp(0, SpriteArchive::instance().get_sprite(sprite_info.sprite_index).number - 1, 1.0 * life / life_max);
    if (life++ == life_max)
        room->del_instance(this);
}