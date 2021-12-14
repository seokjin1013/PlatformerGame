#pragma once

#include <chrono>
#include <ratio>
#include <string>
#include <thread>
#include <vector>
#include "Block.hpp"
#include "BulletBlock.hpp"
#include "Bullet.hpp"
#include "LaserBlock.hpp"
#include "BreakableBlock.hpp"
#include "Button.hpp"
#include "ButtonBlock.hpp"
#include "FlickingBlock.hpp"
#include "Battery.hpp"
#include "Key.hpp"
#include "Console.hpp"
#include "Controller.hpp"
#include "Goal.hpp"
#include "Player.hpp"
#include "View.hpp"
#include "Title.hpp"
#include "HowToPlay.hpp"
#include "StageSelection.hpp"
#include "Room.hpp"
#include "RoomConstructor.hpp"

class PlayManager final {
public:
    static PlayManager& instance();
    PlayManager(const PlayManager&) = delete;
    PlayManager(PlayManager&&) = delete;
    PlayManager& operator=(const PlayManager&) = delete;
    PlayManager& operator=(PlayManager&&) = delete;
    void play();
    std::vector<std::string> str;
    void set_room(RoomIndex room);
    RoomIndex get_room();
    void save_data();
    void load_data();
    int star_count[20];
    bool is_pause = false;

private:
    PlayManager();
    ~PlayManager() = default;
    bool frame_skip_or_waiting();
    std::chrono::high_resolution_clock::time_point previous_time;
    std::chrono::high_resolution_clock::time_point previous_time_real;
    std::chrono::duration<double, std::milli> delayed_time;
    double fps = 0, fps_real = 0, fps_standard = 60;
    RoomIndex current_room = RoomIndex::title;
    bool restart_room = false;
    int restart_room_effect = 0;
    int restart_room_effect_max = 60;
};