#include "Sprite.hpp"

SpriteArchive& SpriteArchive::instance() {
    static SpriteArchive instance;
    return instance;
};

const Sprite& SpriteArchive::get_sprite(SpriteIndex SpriteIndex) {
    return sprite[(int)SpriteIndex];
}

SpriteArchive::SpriteArchive() {
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(Player0.bmp)");
        importer.read_bmp24(R"(Player1.bmp)");
        importer.read_bmp24(R"(Player2.bmp)");
        importer.read_bmp24(R"(Player3.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::player].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::player].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::player].center = { w / 2, h };
        sprite[(int)SpriteIndex::player].size = { w, h };
        sprite[(int)SpriteIndex::player].number = n;
    }
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(PlayerJump0.bmp)");
        importer.read_bmp24(R"(PlayerJump1.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::player_jump].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::player_jump].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::player_jump].center = { w / 2, h };
        sprite[(int)SpriteIndex::player_jump].size = { w, h };
        sprite[(int)SpriteIndex::player_jump].number = n;
    }
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(Block0.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::block].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::block].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::block].center = { w / 2, h / 2 };
        sprite[(int)SpriteIndex::block].size = { w, h };
        sprite[(int)SpriteIndex::block].number = n;
    }
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(BulletShooter0.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::bullet_shooter].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::bullet_shooter].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::bullet_shooter].center = { w / 2, h / 2 };
        sprite[(int)SpriteIndex::bullet_shooter].size = { w, h };
        sprite[(int)SpriteIndex::bullet_shooter].number = n;
    }
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(Bullet0.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::bullet].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::bullet].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::bullet].center = { w / 2, h / 2 };
        sprite[(int)SpriteIndex::bullet].size = { w, h };
        sprite[(int)SpriteIndex::bullet].number = n;
    }
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(LaserBlock0.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::laser_block].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::laser_block].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::laser_block].center = { w / 2, h / 2 };
        sprite[(int)SpriteIndex::laser_block].size = { w, h };
        sprite[(int)SpriteIndex::laser_block].number = n;
    }
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(Laser0.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::laser].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::laser].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::laser].center = { w / 2, h / 2 };
        sprite[(int)SpriteIndex::laser].size = { w, h };
        sprite[(int)SpriteIndex::laser].number = n;
    }
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(Battery0.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::battery].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::battery].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::battery].center = { w / 2, h / 2 };
        sprite[(int)SpriteIndex::battery].size = { w, h };
        sprite[(int)SpriteIndex::battery].number = n;
    }
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(Key0.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::key].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::key].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::key].center = { w / 2, h / 2 };
        sprite[(int)SpriteIndex::key].size = { w, h };
        sprite[(int)SpriteIndex::key].number = n;
    }
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(Goal0.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::goal].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::goal].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::goal].center = { w / 2, h / 2 };
        sprite[(int)SpriteIndex::goal].size = { w, h };
        sprite[(int)SpriteIndex::goal].number = n;
    }
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(Title0.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::title].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::title].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::title].center = { 0, 0 };
        sprite[(int)SpriteIndex::title].size = { w, h };
        sprite[(int)SpriteIndex::title].number = n;
    }
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(MovableBlock0.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::movable_block].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::movable_block].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::movable_block].center = { w / 2, h / 2 };
        sprite[(int)SpriteIndex::movable_block].size = { w, h };
        sprite[(int)SpriteIndex::movable_block].number = n;
    }
    {
        int w = 0, h = 0, n = 0;
        sprite[(int)SpriteIndex::none].alpha = nullptr;
        sprite[(int)SpriteIndex::none].center = {0, 0};
        sprite[(int)SpriteIndex::none].size = {0, 0};
        sprite[(int)SpriteIndex::none].number = n;
    }
}