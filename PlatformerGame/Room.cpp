#include "Room.hpp"

using namespace std;

Room::Room(const Vec2<double>& size) {
    view_info.size = size;
}

Room::~Room() {
    while (!pool.empty()) {
        Object* e = pool.front();
        delete e;
    }
}

void Room::add_instance(Object& obj) {
    pool.emplace_back(&obj);
}

void Room::del_instance(Object& obj) {
    pool.erase(std::remove(std::begin(pool), std::end(pool), &obj));
}

void Room::step() {
    for (Object* e : pool) {
        e->step();
    }
}

const std::deque<Object*>& Room::get_pool() const {
    return pool;
}

const ViewInfo& Room::get_view_info() const {
    return view_info;
}

void Room::set_view_info_pos(const Vec2<double>& pos) {
    view_info.pos = pos;
}

void Room::set_view_info_size(const Vec2<double>& size) {
    view_info.size = size;
}