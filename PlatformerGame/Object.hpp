#pragma once

#include "Room.hpp"

/*
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
    template <typename T>
    void move_box_collision(Vec2<double>& velocity);
    template <typename T>
    bool check_box_collision(const Vec2<double>& velocity);

protected:
    bool is_box_collide(const Object* const other);
    int get_box_collision_direction(const Vec2<double>& velocity, const Object* const other);
    double get_box_collision_point(const Vec2<double>& velocity, const Object* const other, int dir);
    Vec2<double> pos = {0, 0};
    Room* const room;
    SpriteInfo sprite_info;
};

template <typename T>
void Object::move_box_collision(Vec2<double>& velocity) {
    auto pool = room->get_pool();
    auto pos0 = pos;
    auto pos1 = pos + velocity;
    double min_collision_point = 1;
    int collision_direction = -1;
    for (const auto e : pool) {
        pos = pos1;
        if (e == this) continue;
        if (T* p = dynamic_cast<T*>(e)) {
            if (is_box_collide(e)) {
                pos = pos0;
                int dir = get_box_collision_direction(velocity, e);
                double point = get_box_collision_point(velocity, e, dir);
                if (min_collision_point > point) {
                    min_collision_point = point;
                    collision_direction = dir;
                }
            }
        }
    }
    pos = pos0 + velocity * min_collision_point;
    if (min_collision_point < 1) {
        if (collision_direction & 1)
            velocity.y = 0;
        else
            velocity.x = 0;
        move_box_collision<T>(velocity);
    }
}

template <typename T>
bool Object::check_box_collision(const Vec2<double>& velocity) {
    auto pool = room->get_pool();
    auto pos0 = pos;
    auto pos1 = pos + velocity;
    pos = pos1;
    for (const auto e : pool) {
        if (e == this) continue;
        if (T* p = dynamic_cast<T*>(e)) {
            if (is_box_collide(e)) {
                pos = pos0;
                return true;
            }
        }
    }
    pos = pos0;
    return false;
}

*/