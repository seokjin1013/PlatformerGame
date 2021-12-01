#include "Room.hpp"

using namespace std;

Room::Room(const Vec2<double>& size) {
    view_info.size = size;
}

Room::~Room() {
    Object* e = nullptr;
    while (!pool.empty()) {
        e = pool.front();
        pool.erase(begin(pool));
        delete e;
    }
}

void Room::add_instance(Object* obj) {
    add_register.emplace_back(obj);
    obj->set_room(this);
}

void Room::del_instance(Object* obj) {
    del_register.emplace_back(obj);
}

void Room::step() {
    if (!empty(del_register)) {
        for (Object* e : del_register) {
            if (auto iter = remove(begin(pool), end(pool), e); iter != end(pool)) {
                pool.erase(iter);
                delete e;
            }
        }
        del_register.clear();
    }
    if (!empty(add_register)) {
        pool.insert(end(pool), begin(add_register), end(add_register));
        add_register.clear();
    }
    for (Object* e : pool) {
        e->step();
    }
}

const std::deque<Object*>& Room::get_pool() const {
    return pool;
}

Object::Object(const Vec2<double>& pos) {
    this->pos = pos;
}

const Vec2<double>& Object::get_pos() const {
    return pos;
}

const SpriteInfo& Object::get_sprite_info() const {
    return sprite_info;
}

void Object::set_room(Room* room) {
    this->room = room;
}

bool Object::is_box_collide(const Vec2<double>& velocity, const Object* const other) {
    const auto& spr = SpriteArchive::instance().get_sprite(sprite_info.sprite_index);
    auto ltpos = pos + velocity - spr.center;
    auto rbpos = ltpos + spr.size;
    const auto& o_spr = SpriteArchive::instance().get_sprite(other->sprite_info.sprite_index);
    auto o_ltpos = other->pos - o_spr.center;
    auto o_rbpos = o_ltpos + o_spr.size;
    return o_ltpos.x < rbpos.x&& ltpos.x < o_rbpos.x&& o_ltpos.y < rbpos.y&& ltpos.y < o_rbpos.y;
}

int Object::get_box_collision_direction(const Vec2<double>& velocity, const Object* const other) {
    const auto& spr = SpriteArchive::instance().get_sprite(sprite_info.sprite_index);
    const auto& o_spr = SpriteArchive::instance().get_sprite(other->sprite_info.sprite_index);
    if (velocity.x > 0 && velocity.y > 0) {
        auto rbpos = pos - spr.center + spr.size;
        auto o_ltpos = other->pos - o_spr.center;
        if ((o_ltpos - rbpos).cross(rbpos + velocity - o_ltpos) < 0) return 1;
        return 0;
    }
    if (velocity.x < 0 && velocity.y > 0) {
        auto lbpos = pos - spr.center + Vec2<>{0, (double)spr.size.y};
        auto o_rtpos = other->pos - o_spr.center + Vec2<>{(double)o_spr.size.x, 0};
        if ((o_rtpos - lbpos).cross(lbpos + velocity - o_rtpos) < 0) return 2;
        return 1;
    }
    if (velocity.x < 0 && velocity.y < 0) {
        auto ltpos = pos - spr.center;
        auto o_rbpos = other->pos - o_spr.center + o_spr.size;
        auto ccw = (o_rbpos - ltpos).cross(ltpos + velocity - o_rbpos);
        if (ccw < 0) return 3;
        if (ccw == 0) return -1;
        return 2;
    }
    if (velocity.x > 0 && velocity.y < 0) {
        auto rtpos = pos - spr.center + Vec2<>{(double)spr.size.x, 0};
        auto o_lbpos = other->pos - o_spr.center + Vec2<>{0, (double)o_spr.size.y};
        if ((o_lbpos - rtpos).cross(rtpos + velocity - o_lbpos) <= 0) return 0;
        return 3;
    }
    if (velocity.x > 0) return 0;
    if (velocity.y > 0) return 1;
    if (velocity.x < 0) return 2;
    if (velocity.y < 0) return 3;
    return -1;
}

double Object::get_box_collision_velocity_multiplier(const Vec2<double>& velocity, const Object* const other, int dir) {
    if (dir == -1) return 1;
    const auto& spr = SpriteArchive::instance().get_sprite(sprite_info.sprite_index);
    const auto& o_spr = SpriteArchive::instance().get_sprite(other->sprite_info.sprite_index);
    if (dir == 0) return ((other->pos.x - o_spr.center.x - (spr.size.x - spr.center.x)) - pos.x) / velocity.x;
    if (dir == 1) return ((other->pos.y - o_spr.center.y - (spr.size.y - spr.center.y)) - pos.y) / velocity.y;
    if (dir == 2) return ((other->pos.x + (o_spr.size.x - o_spr.center.x) + (spr.center.x)) - pos.x) / velocity.x;
    return ((other->pos.y + (o_spr.size.y - o_spr.center.y) + (spr.center.y)) - pos.y) / velocity.y;
}