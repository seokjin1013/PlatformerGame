#pragma once

#include "Room.hpp"
#include "Vec2.hpp"
#include "Controller.hpp"
#include "PlayManager.hpp"

class HowToPlay : public Object {
public:
    HowToPlay(const Vec2<double>& pos);
    void step() override;
};