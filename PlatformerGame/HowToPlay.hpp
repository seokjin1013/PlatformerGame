#pragma once

#include "Room.hpp"
#include "Vec2.hpp"
#include "Controller.hpp"
#include "PlayManager.hpp"
#include "Sticker.hpp"
#include "HowToPlayPlayerClone.hpp"

class HowToPlayPlayerClone;

class HowToPlay : public Object {
public:
    HowToPlay(const Vec2<double>& pos);
    void step() override;
private:
    bool created = false;
    bool modified = true;
    Sticker* circle[4];
    Sticker* key[4];
    std::deque<Object*> information;
    HowToPlayPlayerClone* clone = nullptr;
    int page = 0;
    int control_index = 0;
};