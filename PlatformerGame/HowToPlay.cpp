#include "HowToPlay.hpp"

HowToPlay::HowToPlay(const Vec2<double>& pos) : Object(pos) {
    sprite_info.sprite_index = SpriteIndex::how_to_play;
}

void HowToPlay::step() {
    if (Controller::instance().key_pressed(VK_LEFT) && sprite_info.image_index > 0)
        --sprite_info.image_index;
    else if (Controller::instance().key_pressed(VK_RIGHT) &&
        sprite_info.image_index < SpriteArchive::instance().get_sprite(sprite_info.sprite_index).number - 1)
        ++sprite_info.image_index;
    else if (Controller::instance().key_pressed(VK_ESCAPE) ||
        Controller::instance().key_pressed(VK_BACK) ||
        Controller::instance().key_pressed('X'))
        PlayManager::instance().set_room(RoomIndex::title);
}