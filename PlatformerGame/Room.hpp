#pragma once

#include <algorithm>
#include <deque>
#include "Room.hpp"
#include "Sprite.hpp"
#include "Vec2.hpp"

class Room;
class Object;

struct ViewInfo {
    Vec2<double> pos = {0, 0};
    Vec2<double> size;
    int quake_intensity = 0;
    int time_recall_gauge_show = 0;
    double time_recall_gauge_rate = 0;
    double time_recall_effect_strength = 0;
    double time_recall_effect_period = 0;
    Vec2<double> time_recall_effect_focus;
};

class Room {
public:
    Room(const Vec2<double>& size);
    virtual ~Room();
    void add_instance(Object& object);
    void del_instance(Object& object);
    void step();
    const std::deque<Object*>& get_pool() const;
    int key_flag = 0;
    ViewInfo view_info;

private:
    std::deque<Object*> pool;
};

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
    bool is_box_collide(const Vec2<double>& velocity, const Object* const other);
    int get_box_collision_direction(const Vec2<double>& velocity, const Object* const other);
    double get_box_collision_velocity_multiplier(const Vec2<double>& velocity, const Object* const other, int dir);
    Vec2<double> pos = { 0, 0 };
    Room* const room;
    SpriteInfo sprite_info;
};

template <typename T>
void Object::move_box_collision(Vec2<double>& velocity) {
    auto pool = room->get_pool();
    double min_collision_point = 1;
    int collision_direction = -1;
    for (const auto e : pool) {
        if (e == this) continue;
        if (T* p = dynamic_cast<T*>(e)) {
            if (is_box_collide(velocity, e)) {
                int dir = get_box_collision_direction(velocity, e);
                double point = get_box_collision_velocity_multiplier(velocity, e, dir);
                if (min_collision_point > point) {
                    min_collision_point = point;
                    collision_direction = dir;
                }
            }
        }
    }
    pos += velocity * min_collision_point;
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
    for (const auto e : pool) {
        if (e == this) continue;
        if (T* p = dynamic_cast<T*>(e)) {
            if (is_box_collide(velocity, e)) {
                return true;
            }
        }
    }
    return false;
}