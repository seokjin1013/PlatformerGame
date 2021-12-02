#pragma once

#include "Button.hpp"

Button::Button(const Vec2<double>& pos, bool is_on) : Object(pos) {
    sprite_info.sprite_index = SpriteIndex::button;
    this->is_on = is_on;
    sprite_info.image_index = is_on;
}

void Button::step() {
    if (!collide_with_player && check_box_collision<Player>({ 0, 0 })) {
        collide_with_player = true;
        auto pool = room->get_pool();
        for (auto& e : pool) {
            if (Button* p = dynamic_cast<Button*>(e)) {
                p->toggle();
            }
            else if (ButtonBlockOn* p = dynamic_cast<ButtonBlockOn*>(e)) {
                p->toggle();
            }
            else if (ButtonBlockOff* p = dynamic_cast<ButtonBlockOff*>(e)) {
                p->toggle();
            }
        }
    }
    else if (collide_with_player && !check_box_collision<Player>({ 0, 0 })) {
        collide_with_player = false;
    }
}

void Button::toggle() {
    sprite_info.image_index = is_on = !is_on;
}