#include "MovableBlock.hpp"

MovableBlock::MovableBlock(Room* room, const Vec2<double>& pos) : Block(room, pos) {
    this->sprite_info.sprite_index = SpriteIndex::movable_block;
}

void MovableBlock::step() {
    //velocity calculate
    velocity.y += gravity;
    move_box_collision<Block>(velocity);
    
}