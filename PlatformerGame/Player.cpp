#include "Player.hpp"

using namespace std;

Player::Player(Room* room, const Vec2<double>& pos) : Object(room, pos) {
    this->sprite_info.sprite_index = SpriteIndex::player;
    horizontal_move.negative_vk = VK_LEFT;
    horizontal_move.positive_vk = VK_RIGHT;
    horizontal_move.negative_force = -force;
    horizontal_move.positive_force = force;
    horizontal_move.negative_max = -speed;
    horizontal_move.positive_max = speed;
    Controller::instance().add_control_axis(horizontal_move);
    view_pos_target = pos;
    view_size_target = room->view_info.size;
}

Player::~Player() {
    Controller::instance().del_control_axis(horizontal_move);
}

void Player::step() {
    bool step_on = check_box_collision<Block>(Vec2<double>::DOWN() * 0.001);

    //time recall
    if (Controller::instance().key_down(VK_SPACE)) {
        if (time_recall_gauge > 0) {
            time_recall_sleep = time_recall_sleep_max;
            --time_recall_gauge;
            pos = *player_pos_list.begin();
            velocity = *player_velocity_list.begin();
            player_pos_list.pop_front();
            player_velocity_list.pop_front();
        }
        else {
            PlayManager::instance().set_room(PlayManager::instance().get_room());
        }
    }
    else {
        //velocity calculate
        velocity.x = horizontal_move.value;
        velocity.y += gravity;
        if (Controller::instance().key_down(VK_UP) && step_on)
            velocity.y -= jump;

        //time recall info setting
        if (time_recall_sleep == 0)
            time_recall_gauge = min(time_recall_gauge_max, time_recall_gauge + 1);
        else
            --time_recall_sleep;
        player_pos_list.push_front(pos);
        player_velocity_list.push_front(velocity);
        if (ssize(player_pos_list) > time_recall_gauge_max) player_pos_list.pop_back();
        if (ssize(player_velocity_list) > time_recall_gauge_max) player_velocity_list.pop_back();

        //move
        move_box_collision<Block>(velocity);

        //collide check
        if (check_box_collision<Bullet>(Vec2<double>{0, 0})) PlayManager::instance().set_room(PlayManager::instance().get_room());
        // if(check_box_collision<Battery>(Vec2<double>{0, 0})) score+=1;
    }

    //draw
    if (horizontal_move.direction == -1) sprite_info.image_scale.x = -1;
    if (horizontal_move.direction == 1) sprite_info.image_scale.x = 1;
    if (step_on) {
        sprite_info.sprite_index = SpriteIndex::player;
        if (horizontal_move.direction != 0) {
            if (image_remaining_delay-- == 0) {
                image_remaining_delay = image_delay;
                sprite_info.image_index = (sprite_info.image_index + 1) % SpriteArchive::instance().get_sprite(sprite_info.sprite_index).number;
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

    //view
    ViewInfo& view = room->view_info;
    view_pos_target = pos;
    view.pos = utility::lerp<Vec2<double>>(view.pos, view_pos_target, 0.02);
    view.size = utility::lerp<Vec2<double>>(view.size, view_size_target, 0.02);
    view.time_recall_gauge_rate = 1.0 * time_recall_gauge / time_recall_gauge_max;
    if (Controller::instance().key_down(VK_SPACE)) view.time_recall_gauge_show = 2;
    else if (time_recall_gauge < time_recall_gauge_max) view.time_recall_gauge_show = 1;
    else view.time_recall_gauge_show = 0;

    stringstream ss;
    ss << time_recall_gauge << ' ' << time_recall_sleep;
    PlayManager::instance().str.push_back(ss.str());

    //room reset
    if (Controller::instance().key_pressed('R')) {
        PlayManager::instance().set_room(PlayManager::instance().get_room());
    }
}