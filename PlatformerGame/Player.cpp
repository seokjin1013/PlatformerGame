#include "Player.hpp"

using namespace std;

Player::Player(const Vec2<double>& pos) : Object(pos) {
    sprite_info.sprite_index = SpriteIndex::player;
    horizontal_move.negative_vk = VK_LEFT;
    horizontal_move.positive_vk = VK_RIGHT;
    horizontal_move.negative_force = -force;
    horizontal_move.positive_force = force;
    horizontal_move.negative_max = -speed;
    horizontal_move.positive_max = speed;
    Controller::instance().add_control_axis(horizontal_move);
}

Player::~Player() {
    Controller::instance().del_control_axis(horizontal_move);
    room->add_instance(new Particle(pos, SpriteIndex::player_die, 30));
    PlayManager::instance().set_room(PlayManager::instance().get_room());
    if (!followers.empty()) followers.front()->set_target(nullptr);
}

void Player::step() {
    bool step_on = check_box_collision<Block>(Vec2<double>::DOWN() * epsilon);

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
            room->del_instance(this);
        }
    }
    else {
        //velocity calculate
        velocity.x = horizontal_move.value;
        velocity.y += gravity;
        if (Controller::instance().key_down(VK_UP) && step_on) {
            velocity.y -= jump;
            auto pool = room->get_pool();
            for (auto& e : pool) {
                if (FlickingBlockOn* p = dynamic_cast<FlickingBlockOn*>(e)) {
                    p->toggle();
                }
                else if (FlickingBlockOff* p = dynamic_cast<FlickingBlockOff*>(e)) {
                    if (is_box_collide(velocity, p))
                        room->del_instance(this);
                    p->toggle();
                }
            }
        }

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

        //collide check
        if (check_box_collision<Bullet>(Vec2<double>{0, 0})) room->del_instance(this);
        if (check_box_collision<Battery>(Vec2<double>{0, 0})) battery_count+=1;
    }

    //draw
    if (horizontal_move.direction == -1) sprite_info.image_flip_x = true;
    if (horizontal_move.direction == 1) sprite_info.image_flip_x = false;
    if (step_on) {
        sprite_info.sprite_index = SpriteIndex::player;
        if (horizontal_move.direction != 0) {
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

    //view
    ViewInfo& view = room->view_info;
    view.pos = utility::lerp<Vec2<double>>(view.pos, pos, 0.02);
    if (Controller::instance().key_down(VK_SPACE)) {
        view.time_recall_gauge_show = 2;
        view.time_recall_effect_strength = utility::lerp<double>(view.time_recall_effect_strength, 1, 0.05);
        view.time_recall_gauge_rate = 1.0 * time_recall_gauge / time_recall_gauge_max;
        view.time_recall_effect_period = fmod(view.time_recall_effect_period + 0.02, 1);
        view.time_recall_effect_focus = pos - Vec2<double>{0.0, SpriteArchive::instance().get_sprite(sprite_info.sprite_index).size.y / 2.0};
    }
    else if (time_recall_gauge < time_recall_gauge_max) {
        view.time_recall_gauge_show = 1;
        view.time_recall_effect_strength = utility::lerp<double>(view.time_recall_effect_strength, 0, 0.05);
        view.time_recall_gauge_rate = 1.0 * time_recall_gauge / time_recall_gauge_max;
    }
    else {
        view.time_recall_gauge_show = 0;
        view.time_recall_effect_strength = utility::lerp<double>(view.time_recall_effect_strength, 0, 0.05);
    }

    stringstream ss;
    ss << time_recall_gauge << ' ' << time_recall_sleep;
    PlayManager::instance().str.push_back(ss.str());

    //room reset
    if (Controller::instance().key_pressed('R')) {
        room->del_instance(this);
    }
}