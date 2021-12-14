#include "HowToPlay.hpp"

HowToPlay::HowToPlay(const Vec2<double>& pos) : Object(pos) {
    sprite_info.sprite_index = SpriteIndex::none;
}

void HowToPlay::step() {
    if (!created) {
        room->add_instance(new Sticker({ 0, -108 / 2 + 12 }, SpriteIndex::how_to_play_text, 0, this));
        for (int i = 0; i < 4; ++i) {
            circle[i] = new Sticker(Vec2<int>{ - 18 + 12 * i, 108 / 2 - 12 }, SpriteIndex::how_to_play_circle, (i == page) ? 0 : 1, this);
            room->add_instance(circle[i]);
        }
        room->add_instance(new Sticker(Vec2<int>{ -30, 108 / 2 - 12 }, SpriteIndex::how_to_play_arrow, 0, this));
        room->add_instance(new Sticker(Vec2<int>{ 30, 108 / 2 - 12 }, SpriteIndex::how_to_play_arrow, 1, this));
        created = true;
    }

    if (Controller::instance().key_pressed(VK_LEFT) && page > 0)
        --page, modified = true;
    else if (Controller::instance().key_pressed(VK_RIGHT) && page < 3)
        ++page, modified = true;
    else if (Controller::instance().key_pressed(VK_ESCAPE) ||
        Controller::instance().key_pressed(VK_BACK) ||
        Controller::instance().key_pressed('X'))
        PlayManager::instance().set_room(RoomIndex::title);

    if (modified) {
        for (int i = 0; i < 4; ++i)
            circle[i]->set_image_index((i == page) ? 0 : 1);
        for (auto* e : information)
            room->del_instance(e);
        for (int i = 0; i < 4; ++i)
            key[i] = nullptr;
        clone = nullptr;
        control_index = 0;
        information.clear();
        if (page == 0) {
            information.push_back(key[0] = new Sticker({ -2 - 18, 26 }, SpriteIndex::how_to_play_key, 0, this));
            information.push_back(key[1] = new Sticker({ -2, 26 }, SpriteIndex::how_to_play_key, 2, this));
            information.push_back(new Sticker({ 2, 26 }, SpriteIndex::how_to_play_information, 0, this));
        }
        else if (page == 1) {
            information.push_back(key[2] = new Sticker({ -2, 26 }, SpriteIndex::how_to_play_key, 4, this));
            information.push_back(new Sticker({ 2, 26 }, SpriteIndex::how_to_play_information, 1, this));
        }
        else if (page == 2) {
            information.push_back(key[3] = new Sticker({ -2, 26 }, SpriteIndex::how_to_play_space_bar, 0, this));
            information.push_back(new Sticker({ 2, 26 }, SpriteIndex::how_to_play_information, 2, this));
        }
        else if (page == 3) {
            information.push_back(new Sticker({ -2 - 18 * 3, -20 }, SpriteIndex::how_to_play_key, 6, this));
            information.push_back(new Sticker({ 2 - 18 * 3, -20 }, SpriteIndex::how_to_play_information, 3, this));
            information.push_back(new Sticker({ -2 - 18 * 3, 0 }, SpriteIndex::how_to_play_key, 7, this));
            information.push_back(new Sticker({ 2 - 18 * 3, 0 }, SpriteIndex::how_to_play_information, 4, this));
            information.push_back(new Sticker({ -2 - 18 * 3, 20 }, SpriteIndex::how_to_play_key, 8, this));
            information.push_back(new Sticker({ 2 - 18 * 3, 20 }, SpriteIndex::how_to_play_information, 5, this));
        }
        if (page != 3) {
            information.push_back(clone = new HowToPlayPlayerClone({ 0, -24 }));
            for (int i = -4; i <= 4; ++i)
                information.push_back(new Block(Vec2<int>{ 10 * i, 12 }));
        }
        for (auto* e : information)
            room->add_instance(e);
        modified = false;
    }

    if (page == 0) {
        if (control_index == 40)
            key[0]->set_image_index(1), clone->left_key = true;
        else if (control_index == 80)
            key[0]->set_image_index(0), clone->left_key = false;
        else if (control_index == 100)
            key[1]->set_image_index(3), clone->right_key = true;
        else if (control_index == 140)
            key[1]->set_image_index(2), clone->right_key = false;
        else if (control_index == 160)
            key[1]->set_image_index(3), clone->right_key = true;
        else if (control_index == 190)
            key[1]->set_image_index(2), clone->right_key = false;
        else if (control_index == 200)
            key[0]->set_image_index(1), clone->left_key = true;
        else if (control_index == 230)
            key[0]->set_image_index(0), clone->left_key = false;
        control_index = (control_index + 1) % 240;
    }
    else if (page == 1) {
        if (control_index == 60)
            key[2]->set_image_index(5), clone->up_key = true;
        if (control_index == 65)
            key[2]->set_image_index(4), clone->up_key = false;
        if (control_index == 150)
            key[2]->set_image_index(5), clone->up_key = true;
        if (control_index == 260)
            key[2]->set_image_index(4), clone->up_key = false;
        control_index = (control_index + 1) % 320;
    }
    else if (page == 2) {
        if (control_index == 40)
            clone->left_key = true;
        else if (control_index == 80)
            clone->left_key = false;
        else if (control_index == 100)
            clone->right_key = true;
        else if (control_index == 140)
            clone->up_key = true;
        else if (control_index == 141)
            clone->up_key = false;
        else if (control_index == 170)
            clone->right_key = false, key[3]->set_image_index(1), clone->space_bar_key = true;
        else if (control_index == 300)
            key[3]->set_image_index(0), clone->space_bar_key = false;
        control_index = (control_index + 1) % 320;
    }
}