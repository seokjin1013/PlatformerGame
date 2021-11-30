#include "Title.hpp"

Title::Title(Room* room, const Vec2<double>& pos) : Object(room, pos) {
    this->sprite_info.sprite_index = SpriteIndex::title;
}

void Title::step() {
}