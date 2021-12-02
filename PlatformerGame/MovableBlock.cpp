#include "MovableBlock.hpp"

MovableBlock::MovableBlock(const Vec2<double>& pos) : Block(pos) {
    sprite_info.sprite_index = SpriteIndex::movable_block;
}

void MovableBlock::step() {
    //velocity calculate
    velocity.y += gravity;
    move_box_collision<Block>(velocity);
    
}