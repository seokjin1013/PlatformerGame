#pragma once

#include "Room.hpp"
#include "Vec2.hpp"
#include "utility.hpp"

class Particle : public Object {
public:
    Particle(const Vec2<double>& pos, SpriteIndex sprite_index, int life_max);
    void step() override;
private:
    int life = 0;
    int life_max;
};