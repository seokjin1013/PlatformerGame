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

enum class SpriteIndex { player, player_jump, block, bullet_shooter, bullet, battery, key, goal, none, };

struct SpriteInfo {
    SpriteIndex sprite_index = SpriteIndex::none;
    int image_index = 0;
    Vec2<double> image_scale = {1, 1};
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