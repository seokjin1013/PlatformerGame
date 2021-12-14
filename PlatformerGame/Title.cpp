#include "Title.hpp"

Title::Title(const Vec2<double>& pos) : Object(pos) {
    sprite_info.sprite_index = SpriteIndex::title;
}

void Title::step() {
    if (!press) {
        if (flicking_text_delay == flicking_text_delay_max) {
            sprite_info.image_index = !sprite_info.image_index;
            flicking_text_delay = 0;
        }
        else
            ++flicking_text_delay;
        for (int i = 7; i < 255; ++i)
            if (Controller::instance().key_pressed(i)) {
                room->add_instance(menu[0] = new GuiButton({ 0, 54 - 3 * 14 }, SpriteIndex::gui_menu_button));
                room->add_instance(menu[1] = new GuiButton({ 0, 54 - 3 * 9 }, SpriteIndex::gui_menu_button));
                room->add_instance(menu[2] = new GuiButton({ 0, 54 - 3 * 4 }, SpriteIndex::gui_menu_button));
                room->add_instance(new Sticker(menu[0]->get_pos(), SpriteIndex::text_start, 0, menu[0]));
                room->add_instance(new Sticker(menu[1]->get_pos(), SpriteIndex::text_how, 0, menu[1]));
                room->add_instance(new Sticker(menu[2]->get_pos(), SpriteIndex::text_exit, 0, menu[2]));
                menu[focus]->focus();
                press = true;
                sprite_info.image_index = 0;
            }
    }
    else if (press && !selected) {
        if (Controller::instance().key_pressed(VK_UP)) {
            if (focus > 0) {
                menu[focus--]->unfocus();
                menu[focus]->focus();
            }
        }
        else if (Controller::instance().key_pressed(VK_DOWN)) {
            if (focus < 2) {
                menu[focus++]->unfocus();
                menu[focus]->focus();
            }
        }
        if (Controller::instance().key_pressed(VK_RETURN) || Controller::instance().key_pressed(VK_DOWN)) {
            menu[focus]->trigger();
            selected = true;
        }
    }
    else if (selected) {
        if (menu[0]->is_trigger_end) {
            PlayManager::instance().set_room(RoomIndex::stage_selection);
        }
        else if (menu[1]->is_trigger_end) {
            PlayManager::instance().set_room(RoomIndex::how_to_play);
        }
        else if (menu[2]->is_trigger_end) {
            exit(0);
        }
    }
}