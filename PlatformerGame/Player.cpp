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
    view_size_target = room->get_view_info().size;
}

Player::~Player() {
    Controller::instance().del_control_axis(horizontal_move);
}

void Player::step() {
    //time recall
    if (Controller::instance().key_down(VK_SPACE) && time_recall_gauge > 0) {
        auto it = player_pos_list.begin();      //use iterator
        time_recall_sleep = 90;
        time_recall_gauge -= 0.5;
        if (player_pos_list.size() > 1) {        //if use emtpy, console crash
            it++;
            player_pos_list.pop_front();        //remove deque's front
        }
        pos = *it;
    }
    else {
        if (check_box_collision<Bullet>(Vec2<double>{0, 0})) PlayManager::instance().set_room(PlayManager::instance().get_room());
        player_pos_list.push_front(pos);
        if (time_recall_sleep > 0) time_recall_sleep--;
        if (time_recall_gauge < 100 && time_recall_sleep == 0) time_recall_gauge += 0.125;
        if (player_pos_list.size() > 300) player_pos_list.pop_back();
    }

    //velocity calculate
    velocity.x = horizontal_move.value;
    velocity.y += gravity;

    bool step_on = check_box_collision<Block>(Vec2<double>::DOWN() * 0.001);
    if (Controller::instance().key_down(VK_UP) && step_on)
        velocity.y -= jump;
    move_box_collision<Block>(velocity);

    /*
    if(배터리 먹으면) score+=1;
    */
    //draw
    if (horizontal_move.direction == -1) sprite_info.image_scale.x = -1;
    if (horizontal_move.direction == 1) sprite_info.image_scale.x = 1;
    if (step_on) {
        sprite_info.sprite_index = SpriteIndex::player;
        if (horizontal_move.direction != 0) {
            if (image_remaining_delay == 0) {
                image_remaining_delay = image_delay;
                sprite_info.image_index = (sprite_info.image_index + 1) % SpriteArchive::instance().get_sprite(sprite_info.sprite_index).number;
            }
            --image_remaining_delay;
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
    const ViewInfo& view = room->get_view_info();
    view_pos_target = pos;
    room->set_view_info_pos(utility::lerp<Vec2<double>>(view.pos, view_pos_target, 0.02));
    room->set_view_info_size(utility::lerp<Vec2<double>>(view.size, view_size_target, 0.02));

    //room reset
    if (Controller::instance().key_pressed('R')) {
        PlayManager::instance().set_room(PlayManager::instance().get_room());
    }
}