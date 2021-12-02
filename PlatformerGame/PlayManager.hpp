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
#include "Laser.hpp"
#include "MovableBlock.hpp"
#include "BreakableBlock.hpp"
#include "Button.hpp"
#include "ButtonBlock.hpp"
#include "Battery.hpp"
#include "Key.hpp"
#include "Console.hpp"
#include "Controller.hpp"
#include "Goal.hpp"
#include "Player.hpp"
#include "View.hpp"
#include "Title.hpp"
#include "Room.hpp"

class PlayManager final {
public:
    static PlayManager& instance();
    PlayManager(const PlayManager&) = delete;
    PlayManager(PlayManager&&) = delete;
    PlayManager& operator=(const PlayManager&) = delete;
    PlayManager& operator=(PlayManager&&) = delete;
    void play();
    std::vector<std::string> str;
    void set_room(int room);
    int get_room();

private:
    PlayManager();
    ~PlayManager() = default;
    bool frame_skip_or_waiting();
    std::chrono::high_resolution_clock::time_point previous_time;
    std::chrono::high_resolution_clock::time_point previous_time_real;
    std::chrono::duration<double, std::milli> delayed_time;
    double fps = 0, fps_real = 0, fps_standard = 60;
    int current_room = 0;
    bool restart_room = false;
};