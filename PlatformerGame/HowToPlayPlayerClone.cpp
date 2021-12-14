#include "HowToPlayPlayerClone.hpp"

using namespace std;

HowToPlayPlayerClone::HowToPlayPlayerClone(const Vec2<double>& pos) : Object(pos) {
    sprite_info.sprite_index = SpriteIndex::player;
    left_key = right_key = up_key = space_bar_key = false;
}

HowToPlayPlayerClone::~HowToPlayPlayerClone() {
}

void HowToPlayPlayerClone::step() {
    bool step_on = check_box_collision<Block>(Vec2<double>::DOWN() * epsilon);

    move_direction = right_key - left_key;
    if (move_direction > 0)
        move_value = min(speed, move_value + force);
    else if (move_direction < 0)
        move_value = max(-speed, move_value - force);
    else
        move_value = utility::median<double>(move_value - force, move_value + force, 0);

    //time recall
    if (space_bar_key) {
        if (time_recall_gauge > 0) {
            time_recall_sleep = time_recall_sleep_max;
            --time_recall_gauge;
            pos = *player_pos_list.begin();
            velocity = *player_velocity_list.begin();
            player_pos_list.pop_front();
            player_velocity_list.pop_front();
        }
        else {
            room->del_instance(this);
        }
    }
    else {
        //velocity calculate
        velocity.x = move_value;
        velocity.y += gravity;
        if (up_key && step_on)
            velocity.y -= jump;

        //time recall info setting
        if (time_recall_sleep == 0)
            time_recall_gauge = min(time_recall_gauge_max, time_recall_gauge + 2);
        else
            --time_recall_sleep;
        player_pos_list.push_front(pos);
        player_velocity_list.push_front(velocity);
        if (ssize(player_pos_list) > time_recall_gauge_max) player_pos_list.pop_back();
        if (ssize(player_velocity_list) > time_recall_gauge_max) player_velocity_list.pop_back();

        //move
        move_box_collision<Block>(velocity);
    }

    //draw
    if (move_direction == -1) sprite_info.image_flip_x = true;
    if (move_direction == 1) sprite_info.image_flip_x = false;
    if (step_on) {
        sprite_info.sprite_index = SpriteIndex::player;
        if (move_direction != 0) {
            if (image_remaining_delay-- == 0) {
                image_remaining_delay = image_delay;
                sprite_info.image_index = (sprite_info.image_index + 1)
                    % SpriteArchive::instance().get_sprite(sprite_info.sprite_index).number;
            }
        }
        else {
            sprite_info.image_index = 0;
            image_remaining_delay = 0;
        }
    }
    else {
        sprite_info.sprite_index = SpriteIndex::player_jump;
        if (velocity.y < 0)
            sprite_info.image_index = 0;
        else
            sprite_info.image_index = 1;
    }
}