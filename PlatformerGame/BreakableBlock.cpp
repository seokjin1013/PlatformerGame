#include "BreakableBlock.hpp"

BreakableBlock::BreakableBlock(const Vec2<double>& pos) : Block(pos) {
    this->sprite_info.sprite_index = SpriteIndex::breakable_block;
}

void BreakableBlock::step() {
    if (breaking) {
        if (life == 0) {
            room->del_instance(this);
        }
        else {
            sprite_info.image_index = utility::lerp(0, SpriteArchive::instance().get_sprite(sprite_info.sprite_index).number,
                (1.0 * life_max - life) / life_max);
            --life;
        }
    }
    else if (check_box_collision<Player>(Vec2<double>::UP() * epsilon))
        breaking = true;
}