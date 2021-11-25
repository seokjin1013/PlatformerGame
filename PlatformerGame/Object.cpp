#include "Object.hpp"

Object::Object(Room* room) : room(room) {
    room->add_instance(*this);
}

Object::Object(Room* room, const Vec2<double>& pos) : Object(room) {
    this->pos = pos;
}

Object::~Object() {
    room->del_instance(*this);
}

const Vec2<double>& Object::get_pos() const {
    return pos;
}

const SpriteInfo& Object::get_sprite_info() const {
    return sprite_info;
}

bool Object::is_box_collide(const Object* const other) {
    const auto& spr = SpriteArchive::instance().get_sprite(sprite_info.sprite_index);
    auto ltpos = pos - spr.center;
    auto rbpos = ltpos + spr.size;
    const auto& o_spr = SpriteArchive::instance().get_sprite(other->sprite_info.sprite_index);
    auto o_ltpos = other->pos - o_spr.center;
    auto o_rbpos = o_ltpos + o_spr.size;
    return o_ltpos.x < rbpos.x && ltpos.x < o_rbpos.x && o_ltpos.y < rbpos.y && ltpos.y < o_rbpos.y;
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

double Object::get_box_collision_point(const Vec2<double>& velocity, const Object* const other, int dir) {
    if (dir == -1) return 1;
    const auto& spr = SpriteArchive::instance().get_sprite(sprite_info.sprite_index);
    const auto& o_spr = SpriteArchive::instance().get_sprite(other->sprite_info.sprite_index);
    if (dir == 0) return ((other->pos.x - o_spr.center.x - (spr.size.x - spr.center.x)) - pos.x) / velocity.x;
    if (dir == 1) return ((other->pos.y - o_spr.center.y - (spr.size.y - spr.center.y)) - pos.y) / velocity.y;
    if (dir == 2) return ((other->pos.x + (o_spr.size.x - o_spr.center.x) + (spr.center.x)) - pos.x) / velocity.x;
    return ((other->pos.y + (o_spr.size.y - o_spr.center.y) + (spr.center.y)) - pos.y) / velocity.y;
}