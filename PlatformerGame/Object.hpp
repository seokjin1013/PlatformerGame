#pragma once

#include "Room.hpp"
#include "Sprite.hpp"

class Room;
class Object;

class Object {
public:
    Object(Room* room);
    Object(Room* room, const Vec2<double>& pos);
    virtual ~Object();
    virtual void step() = 0;
    const Vec2<double>& get_pos() const;
    const SpriteInfo& get_sprite_info() const;

protected:
    bool is_box_collide(const Object* const other);
    int get_box_collision_direction(const Vec2<double>& velocity, const Object* const other);
    double get_box_collision_point(const Vec2<double>& velocity, const Object* const other, int dir);
    Vec2<double> pos = {0, 0};
    Room* const room;
    SpriteInfo sprite_info;
};