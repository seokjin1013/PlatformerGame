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
                room->add_instance(menu[0] = new GuiButton(Vec2<int>{0, 9} *1, SpriteIndex::gui_button_start));
                room->add_instance(menu[1] = new GuiButton(Vec2<int>{0, 9} *3, SpriteIndex::gui_button_how));
                room->add_instance(menu[2] = new GuiButton(Vec2<int>{0, 9} *5, SpriteIndex::gui_button_exit));
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
        if (Controller::instance().key_pressed(VK_RETURN)) {
            menu[focus]->trigger();
            selected = true;
        }
    }
    else if (selected) {
        if (menu[0]->is_trigger_end) {
            PlayManager::instance().set_room(RoomIndex::stage1);
        }
        else if (menu[1]->is_trigger_end) {
            PlayManager::instance().set_room(RoomIndex::stage2);
        }
        else if (menu[2]->is_trigger_end) {
            exit(0);
        }
    }
}