#include "Title.hpp"

Title::Title(const Vec2<double>& pos) : Object(pos) {
    sprite_info.sprite_index = SpriteIndex::title;
}

void Title::step() {
}