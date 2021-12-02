#include "LaserBlock.hpp"

LaserBlock::LaserBlock(const Vec2<double>& pos, int rotate) : Block(pos) {
    this->rotate = rotate;
    sprite_info.sprite_index = SpriteIndex::laser_block;
    sprite_info.image_angle = rotate;
    if (rotate == 0) dpos = { 4, 0 };
    else if (rotate == 1) dpos = { 0, 4 };
    else if (rotate == 2) dpos = { -4, 0 };
    else if (rotate == 3) dpos = { 0, -4 };
}

void LaserBlock::step() {
    auto pool = room->get_pool();
    laser_range = laser_range_max;
    for (auto* e : pool) {
        if (e == this) continue;
        if (Block* p = dynamic_cast<Block*>(e)) {
            const auto& spr = SpriteArchive::instance().get_sprite(sprite_info.sprite_index);
            auto ltpos = pos - laser_thinness / 2;
            auto rbpos = ltpos + (laser_thinness - 1);
            const auto& o_spr = SpriteArchive::instance().get_sprite(p->get_sprite_info().sprite_index);
            auto o_ltpos = p->get_pos() - o_spr.center;
            auto o_rbpos = o_ltpos + o_spr.size;
            if (rotate & 1) {
                if (o_ltpos.x < rbpos.x && ltpos.x < o_rbpos.x)
                    if (double range = get_box_collision_velocity_multiplier(dpos, e, rotate); range >= 0)
                        laser_range = min(laser_range, range);
            }
            else {
                if (o_ltpos.y < rbpos.y && ltpos.y < o_rbpos.y)
                    if (double range = get_box_collision_velocity_multiplier(dpos, e, rotate); range >= 0)
                        laser_range = min(laser_range, range);
            }
        }
    }
    if (rotate == 0) {
        sprite_info.primary = true;
        sprite_info.x1 = static_cast<int>(dpos.x);
        sprite_info.x2 = static_cast<int>(dpos.x + dpos.x * laser_range);
        sprite_info.y1 = -laser_thinness / 2;
        sprite_info.y2 = -laser_thinness / 2 + laser_thinness - 1;
    }
    if (rotate == 1) {
        sprite_info.primary = true;
        sprite_info.x1 = -laser_thinness / 2;
        sprite_info.x2 = -laser_thinness / 2 + laser_thinness - 1;
        sprite_info.y1 = static_cast<int>(dpos.y);
        sprite_info.y2 = static_cast<int>(dpos.y + dpos.y * laser_range);
    }
    if (rotate == 2) {
        sprite_info.primary = true;
        sprite_info.x1 = static_cast<int>(dpos.x + dpos.x * laser_range);
        sprite_info.x2 = static_cast<int>(dpos.x);
        sprite_info.y1 = -laser_thinness / 2;
        sprite_info.y2 = -laser_thinness / 2 + laser_thinness - 1;
    }
    if (rotate == 3) {
        sprite_info.primary = true;
        sprite_info.x1 = -laser_thinness / 2;
        sprite_info.x2 = -laser_thinness / 2 + laser_thinness - 1;
        sprite_info.y1 = static_cast<int>(dpos.y + dpos.y * laser_range);
        sprite_info.y2 = static_cast<int>(dpos.y);
    }
    for (auto e : pool) {
        if (Player* p = dynamic_cast<Player*>(e)) {
            auto ltpos = pos + Vec2<double>{static_cast<double>(sprite_info.x1), static_cast<double>(sprite_info.y1)};
            auto rbpos = pos + Vec2<double>{static_cast<double>(sprite_info.x2), static_cast<double>(sprite_info.y2)};
            const auto& o_spr = SpriteArchive::instance().get_sprite(p->get_sprite_info().sprite_index);
            auto o_ltpos = p->get_pos() - o_spr.center;
            auto o_rbpos = o_ltpos + o_spr.size;
            if (o_ltpos.x < rbpos.x && ltpos.x < o_rbpos.x && o_ltpos.y < rbpos.y && ltpos.y < o_rbpos.y) {
                room->del_instance(e);
            }
        }
        else if (Bullet* p = dynamic_cast<Bullet*>(e)) {
            auto ltpos = pos + Vec2<double>{static_cast<double>(sprite_info.x1), static_cast<double>(sprite_info.y1)};
            auto rbpos = pos + Vec2<double>{static_cast<double>(sprite_info.x2), static_cast<double>(sprite_info.y2)};
            const auto& o_spr = SpriteArchive::instance().get_sprite(p->get_sprite_info().sprite_index);
            auto o_ltpos = p->get_pos() - o_spr.center;
            auto o_rbpos = o_ltpos + o_spr.size;
            if (o_ltpos.x < rbpos.x && ltpos.x < o_rbpos.x && o_ltpos.y < rbpos.y && ltpos.y < o_rbpos.y) {
                room->del_instance(e);
            }
        }
    }
}