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
};

class Room {
public:
    Room(const Vec2<double>& size);
    virtual ~Room();
    void add_instance(Object& object);
    void del_instance(Object& object);
    void step();
    const std::deque<Object*>& get_pool() const;
    const ViewInfo& get_view_info() const;
    void set_view_info_pos(const Vec2<double>& pos);
    void set_view_info_size(const Vec2<double>& pos);
    int key_flag = 0;

private:
    std::deque<Object*> pool;
    ViewInfo view_info;
};