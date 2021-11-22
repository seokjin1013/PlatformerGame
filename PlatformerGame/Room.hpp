#pragma once

#include <algorithm>
#include <deque>
#include "Object.hpp"
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