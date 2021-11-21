#pragma once

#define NOMINMAX
#include <windows.h>
#include <algorithm>
#include <cstring>
#include <deque>
#include "Utility.hpp"

struct ControlAxis {
    int negative_vk, positive_vk;
    double negative_max, positive_max;
    double negative_force, positive_force;
    double value = 0;
    int direction;
};

class Controller final {
public:
    static Controller& instance();
    Controller(const Controller&) = delete;
    Controller(Controller&&) = delete;
    Controller& operator=(const Controller&) = delete;
    Controller& operator=(Controller&&) = delete;
    void step();
    bool key_pressed(int vk);
    bool key_down(int vk);
    bool key_released(int vk);
    void add_control_axis(ControlAxis& control_axis);
    void del_control_axis(ControlAxis& control_axis);

private:
    Controller();
    ~Controller() = default;
    bool previous_key[255];
    bool key[255];
    std::deque<ControlAxis*> control_axises;
};