#pragma once
#include <cstdlib>
#include "Vec2.hpp"
#include "SpriteImporter.hpp"

struct Sprite {
    Vec2<int> center;
    Vec2<int> size;
    int* alpha;
    int number;
};

enum class SpriteIndex { 
    key, goal, title, battery, star, pause,
    how_to_play_text, how_to_play_information, how_to_play_key, how_to_play_space_bar, how_to_play_arrow, how_to_play_circle,
    stage_selection_text, stage_selection_difficulty, stage_selection_lock,
    player, player_jump, player_die,
    block, breakable_block, 
    bullet_block, bullet, 
    laser_block,
    button_block, button,
    flicking_block,
    gui_menu_button, gui_level_button,
    text_start, text_how, text_exit,
    text_stage_number,
    none
};

struct SpriteInfo {
    SpriteIndex sprite_index = SpriteIndex::none;
    int image_index = 0;
    bool image_flip_x = false;
    bool image_flip_y = false;
    int image_angle = 0;

    bool primary = false;
    int x1, x2, y1, y2;
};

class SpriteArchive final {
public:
    static SpriteArchive& instance();
    SpriteArchive(const SpriteArchive&) = delete;
    SpriteArchive(SpriteArchive&&) = delete;
    Sprite& operator=(const SpriteArchive&) = delete;
    Sprite& operator=(SpriteArchive&&) = delete;
    const Sprite& get_sprite(SpriteIndex sprite_index);

private:
    SpriteArchive();
    Sprite sprite[1000];
};