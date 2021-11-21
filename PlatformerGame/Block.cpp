#include "Block.hpp"

Block::Block(Room* room, const Vec2<double>& pos) : Object(room, pos) {
    this->sprite_info.sprite_index = SpriteIndex::block;
}

void Block::step() {
}