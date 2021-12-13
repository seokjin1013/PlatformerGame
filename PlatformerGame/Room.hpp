#pragma once

#include <algorithm>
#include <deque>
#include "Sprite.hpp"
#include "Vec2.hpp"

class Room;
class Object;

enum class RoomIndex {
    title, how_to_play, stage_selection,
    stage1, stage2, stage3, stage4, stage5,
    stage6, stage7, stage8, stage9, stage10,
    stage11, stage12, stage13, stage14, stage15,
    stage16, stage17, stage18, stage19, stage20,
    none
};

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
    void add_instance(Object* object);
    void del_instance(Object* object);
    void step();
    const std::deque<Object*>& get_pool() const;
    int key_flag = 0;
    ViewInfo view_info;

private:
    std::deque<Object*> pool;
    std::deque<Object*> add_register, del_register;
};

class Object {
public:
    Object(const Vec2<double>& pos);
    virtual ~Object() = default;
    virtual void step() = 0;
    const Vec2<double>& get_pos() const;
    const SpriteInfo& get_sprite_info() const;
    void set_room(Room* room);
    template <typename T>
    void move_box_collision(Vec2<double>& velocity);
    template <typename T>
    bool check_box_collision(const Vec2<double>& velocity);

protected:
    bool is_box_collide(const Vec2<double>& velocity, const Object* const other);
    int get_box_collision_direction(const Vec2<double>& velocity, const Object* const other);
    double get_box_collision_velocity_multiplier(const Vec2<double>& velocity, const Object* const other, int dir);
    Vec2<double> pos = { 0, 0 };
    Room* room = nullptr;
    SpriteInfo sprite_info;
};

#include "Room.inl"