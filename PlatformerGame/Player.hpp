#pragma once

#include <windows.h>
#include <sstream>
#include <deque>
#include "Controller.hpp"
#include "Object.hpp"
#include "PlayManager.hpp"
#include "Bullet.hpp"
#include "Battery.hpp"
#include "Vec2.hpp"

class Block;
class Bullet_shooter;

class Player : public Object {
public:
    Player(Room* room, const Vec2<double>& pos);
    virtual ~Player();
    void step() override;

private:
    template <typename T>
    void move_box_collision(Vec2<double>& velocity);
    template <typename T>
    bool check_box_collision(const Vec2<double>& velocity);
    ControlAxis horizontal_move;
    Vec2<double> velocity = { 0, 0 };
    double speed = 0.9, force = 0.15, gravity = 0.05, jump = 1.5;

    int time_recall_sleep = 0;
    double time_recall_gauge = 0.0;
    std::deque<Vec2<double>> player_pos_list;

    int image_delay = 10;
    int image_remaining_delay = 0;
    Vec2<double> view_pos_target;
    Vec2<int> view_size_target;
};

template <typename T>
void Player::move_box_collision(Vec2<double>& velocity) {
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
bool Player::check_box_collision(const Vec2<double>& velocity) {
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