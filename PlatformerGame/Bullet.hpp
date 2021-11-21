#pragma once

#include "Object.hpp"
#include "Vec2.hpp"
#include "Block.hpp"

class Bullet : public Object {
private:
    template <typename T>
    void move_box_collision(Vec2<double>& velocity);
    template <typename T>
    bool check_box_collision(const Vec2<double>& velocity);
public:
    Bullet(Room* room, const Vec2<double>& pos);
    void step() override;
};

template <typename T>
void Bullet::move_box_collision(Vec2<double>& velocity) {
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
        velocity *= (1 - min_collision_point);
        if (collision_direction & 1)
            velocity.y = 0;
        else
            velocity.x = 0;
        move_box_collision<T>(velocity);
    }
}

template <typename T>
bool Bullet::check_box_collision(const Vec2<double>& velocity) {
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