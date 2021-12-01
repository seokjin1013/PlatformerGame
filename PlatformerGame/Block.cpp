#include "Block.hpp"

Block::Block(const Vec2<double>& pos) : Object(pos) {
    this->sprite_info.sprite_index = SpriteIndex::block;
}

void Block::step() {
}