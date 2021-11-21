#include "Controller.hpp"

using namespace std;

Controller& Controller::instance() {
    static Controller instance;
    return instance;
}

void Controller::step() {
    memcpy(previous_key, key, sizeof(previous_key));
    for (int i = 0; i < 255; ++i)
        key[i] = GetAsyncKeyState(i);
    for (auto* e : control_axises) {
        e->direction = key[e->positive_vk] - key[e->negative_vk];
        if (e->direction > 0)
            e->value = min(e->positive_max, e->value + e->positive_force);
        else if (e->direction < 0)
            e->value = max(e->negative_max, e->value + e->negative_force);
        else
            e->value = utility::median<double>(e->value + e->negative_force, e->value + e->positive_force, 0);
    }
}

bool Controller::key_pressed(int vk) {
    return !previous_key[vk] && key[vk];
}

bool Controller::key_down(int vk) {
    return key[vk];
}

bool Controller::key_released(int vk) {
    return previous_key[vk] && !key[vk];
}

Controller::Controller() {
    memset(key, 0, sizeof(key));
}

void Controller::add_control_axis(ControlAxis& control_axis) {
    control_axises.emplace_back(&control_axis);
}

void Controller::del_control_axis(ControlAxis& control_axis) {
    control_axises.erase(remove(begin(control_axises), end(control_axises), &control_axis));
}
