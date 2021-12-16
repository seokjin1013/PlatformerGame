#include "StageSelection.hpp"

StageSelection::StageSelection(const Vec2<double>& pos) : Object(pos) {
    sprite_info.sprite_index = SpriteIndex::none;
    int star0 = 20, star3 = 20;
    for (int i = 19; i >= 0; --i) {
        if (PlayManager::instance().stage_star_count[i] == 0)
            star0 = i;
        if (PlayManager::instance().stage_star_count[i] < 3)
            star3 = i;
    }
    if (star3 == 20)
        focus = 0;
    else if (star0 == 20)
        focus = star3;
    else
        focus = star0;
}

bool is_stage_unlocked(int stage) {
    if (stage == 0) return true;
    if (stage != 10 && stage != 15 && PlayManager::instance().stage_star_count[stage - 1] > 0) return true;
    if ((stage == 10 || stage == 15) && PlayManager::instance().stage_star_count[4] > 0) return true;
    return false;
}

void StageSelection::step() {
    if (!level_button_create) {
        level_button_create = true;
        room->add_instance(new Sticker(Vec2<int>{0, -108 / 2 + 12}, SpriteIndex::stage_selection_text, 0, this));
        for (int i = 0; i < 4; ++i) {
            room->add_instance(new Sticker(Vec2<int>{25, 20} *Vec2<int>{ -2, i - 1 } + Vec2<int>{0, 3}, SpriteIndex::stage_selection_difficulty, i, this));
            for (int j = 0; j < 5; ++j) {
                room->add_instance(stage[i * 5 + j] = new GuiButton(Vec2<int>{25, 20} *Vec2<int>{ j - 1, i - 1 } + Vec2<int>{-3, 0}, SpriteIndex::gui_level_button));
                if (is_stage_unlocked(i * 5 + j)) {
                    room->add_instance(new Sticker(stage[i * 5 + j]->get_pos(), SpriteIndex::text_stage_number, i * 5 + j + 1, stage[i * 5 + j]));
                    for (int k = 0; k < PlayManager::instance().stage_star_count[i * 5 + j]; ++k)
                        room->add_instance(new Sticker(stage[i * 5 + j]->get_pos() + Vec2<int>{ -6 + 6 * k, 8 }, SpriteIndex::star, 0, stage[i * 5 + j]));
                }
                else
                    room->add_instance(new Sticker(stage[i * 5 + j]->get_pos(), SpriteIndex::stage_selection_lock, 0, stage[i * 5 + j]));
            }
        }
        stage[focus]->focus();
    }
    else if (level_button_create && !selected) {
        int nxt_focus = focus;
        if (Controller::instance().key_pressed(VK_UP))
            nxt_focus -= 5;
        if (Controller::instance().key_pressed(VK_DOWN))
            nxt_focus += 5;
        if (Controller::instance().key_pressed(VK_LEFT))
            nxt_focus -= 1;
        if (Controller::instance().key_pressed(VK_RIGHT))
            nxt_focus += 1;
        if (nxt_focus != focus && nxt_focus >= 0 && nxt_focus < 20) {
            stage[focus]->unfocus();
            focus = nxt_focus;
            stage[focus]->focus();
        }
        if (Controller::instance().key_pressed(VK_RETURN) || Controller::instance().key_pressed(VK_SPACE)) {
            if (is_stage_unlocked(focus)) {
                stage[focus]->trigger();
                selected = true;
            }
            else {
                stage[focus]->denied();
            }
        }
    }
    else if (selected) {
        if (stage[focus]->is_trigger_end) {
            RoomIndex stage_to_room_index[20] = {
                RoomIndex::stage1,RoomIndex::stage2,RoomIndex::stage3,RoomIndex::stage4,RoomIndex::stage5,
                RoomIndex::stage6,RoomIndex::stage7,RoomIndex::stage8,RoomIndex::stage9,RoomIndex::stage10,
                RoomIndex::stage11,RoomIndex::stage12,RoomIndex::stage13,RoomIndex::stage14,RoomIndex::stage15,
                RoomIndex::stage16,RoomIndex::stage17,RoomIndex::stage18,RoomIndex::stage19,RoomIndex::stage20,
            };
            PlayManager::instance().set_room(stage_to_room_index[focus]);
        }
    }
    if (Controller::instance().key_pressed(VK_ESCAPE) ||
        Controller::instance().key_pressed(VK_BACK) ||
        Controller::instance().key_pressed('X'))
        PlayManager::instance().set_room(RoomIndex::title);
}