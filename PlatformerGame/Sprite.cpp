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
        importer.read_bmp24(R"(BulletBlock0.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::bullet_block].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::bullet_block].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::bullet_block].center = { w / 2, h / 2 };
        sprite[(int)SpriteIndex::bullet_block].size = { w, h };
        sprite[(int)SpriteIndex::bullet_block].number = n;
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
        importer.read_bmp24(R"(Title1.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::title].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::title].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::title].center = { 0, 0 };
        sprite[(int)SpriteIndex::title].size = { w, h };
        sprite[(int)SpriteIndex::title].number = n;
    }
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(HowToPlay0.bmp)");
        importer.read_bmp24(R"(HowToPlay1.bmp)");
        importer.read_bmp24(R"(HowToPlay2.bmp)");
        importer.read_bmp24(R"(HowToPlay3.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::how_to_play].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::how_to_play].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::how_to_play].center = { 0, 0 };
        sprite[(int)SpriteIndex::how_to_play].size = { w, h };
        sprite[(int)SpriteIndex::how_to_play].number = n;
    }
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(StageSelection0.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::stage_selection].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::stage_selection].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::stage_selection].center = { 0, 0 };
        sprite[(int)SpriteIndex::stage_selection].size = { w, h };
        sprite[(int)SpriteIndex::stage_selection].number = n;
    }
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(BreakableBlock0.bmp)");
        importer.read_bmp24(R"(BreakableBlock1.bmp)");
        importer.read_bmp24(R"(BreakableBlock2.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::breakable_block].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::breakable_block].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::breakable_block].center = { w / 2, h / 2 };
        sprite[(int)SpriteIndex::breakable_block].size = { w, h };
        sprite[(int)SpriteIndex::breakable_block].number = n;
    }
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(Button0.bmp)");
        importer.read_bmp24(R"(Button1.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::button].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::button].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::button].center = { w / 2, h / 2 };
        sprite[(int)SpriteIndex::button].size = { w, h };
        sprite[(int)SpriteIndex::button].number = n;
    }
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(ButtonBlock0.bmp)");
        importer.read_bmp24(R"(ButtonBlock1.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::button_block].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::button_block].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::button_block].center = { w / 2, h / 2 };
        sprite[(int)SpriteIndex::button_block].size = { w, h };
        sprite[(int)SpriteIndex::button_block].number = n;
    }
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(FlickingBlock0.bmp)");
        importer.read_bmp24(R"(FlickingBlock1.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::flicking_block].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::flicking_block].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::flicking_block].center = { w / 2, h / 2 };
        sprite[(int)SpriteIndex::flicking_block].size = { w, h };
        sprite[(int)SpriteIndex::flicking_block].number = n;
    }
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(GuiMenuButton0.bmp)");
        importer.read_bmp24(R"(GuiMenuButton1.bmp)");
        importer.read_bmp24(R"(GuiMenuButton2.bmp)");
        importer.read_bmp24(R"(GuiMenuButton3.bmp)");
        importer.read_bmp24(R"(GuiMenuButton4.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::gui_menu_button].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::gui_menu_button].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::gui_menu_button].center = { w / 2, h / 2 };
        sprite[(int)SpriteIndex::gui_menu_button].size = { w, h };
        sprite[(int)SpriteIndex::gui_menu_button].number = n;
    }
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(GuiLevelButton0.bmp)");
        importer.read_bmp24(R"(GuiLevelButton1.bmp)");
        importer.read_bmp24(R"(GuiLevelButton2.bmp)");
        importer.read_bmp24(R"(GuiLevelButton3.bmp)");
        importer.read_bmp24(R"(GuiLevelButton4.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::gui_level_button].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::gui_level_button].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::gui_level_button].center = { w / 2, h / 2 };
        sprite[(int)SpriteIndex::gui_level_button].size = { w, h };
        sprite[(int)SpriteIndex::gui_level_button].number = n;
    }
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(TextStart0.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::text_start].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::text_start].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::text_start].center = { w / 2, h / 2 };
        sprite[(int)SpriteIndex::text_start].size = { w, h };
        sprite[(int)SpriteIndex::text_start].number = n;
    }
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(TextHow0.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::text_how].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::text_how].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::text_how].center = { w / 2, h / 2 };
        sprite[(int)SpriteIndex::text_how].size = { w, h };
        sprite[(int)SpriteIndex::text_how].number = n;
    }
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(TextExit0.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::text_exit].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::text_exit].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::text_exit].center = { w / 2, h / 2 };
        sprite[(int)SpriteIndex::text_exit].size = { w, h };
        sprite[(int)SpriteIndex::text_exit].number = n;
    }
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(TextStageNumber0.bmp)");
        importer.read_bmp24(R"(TextStageNumber1.bmp)");
        importer.read_bmp24(R"(TextStageNumber2.bmp)");
        importer.read_bmp24(R"(TextStageNumber3.bmp)");
        importer.read_bmp24(R"(TextStageNumber4.bmp)");
        importer.read_bmp24(R"(TextStageNumber5.bmp)");
        importer.read_bmp24(R"(TextStageNumber6.bmp)");
        importer.read_bmp24(R"(TextStageNumber7.bmp)");
        importer.read_bmp24(R"(TextStageNumber8.bmp)");
        importer.read_bmp24(R"(TextStageNumber9.bmp)");
        importer.read_bmp24(R"(TextStageNumber10.bmp)");
        importer.read_bmp24(R"(TextStageNumber11.bmp)");
        importer.read_bmp24(R"(TextStageNumber12.bmp)");
        importer.read_bmp24(R"(TextStageNumber13.bmp)");
        importer.read_bmp24(R"(TextStageNumber14.bmp)");
        importer.read_bmp24(R"(TextStageNumber15.bmp)");
        importer.read_bmp24(R"(TextStageNumber16.bmp)");
        importer.read_bmp24(R"(TextStageNumber17.bmp)");
        importer.read_bmp24(R"(TextStageNumber18.bmp)");
        importer.read_bmp24(R"(TextStageNumber19.bmp)");
        importer.read_bmp24(R"(TextStageNumber20.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::text_stage_number].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::text_stage_number].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::text_stage_number].center = { w / 2, h / 2 };
        sprite[(int)SpriteIndex::text_stage_number].size = { w, h };
        sprite[(int)SpriteIndex::text_stage_number].number = n;
    }
    {
        SpriteImporter importer;
        importer.read_bmp24(R"(Star0.bmp)");
        auto [spr, w, h, n] = importer.get();
        sprite[(int)SpriteIndex::star].alpha = new int[w * h * n];
        memcpy(sprite[(int)SpriteIndex::star].alpha, spr, sizeof(int) * w * h * n);
        sprite[(int)SpriteIndex::star].center = { w / 2, h / 2 };
        sprite[(int)SpriteIndex::star].size = { w, h };
        sprite[(int)SpriteIndex::star].number = n;
    }
    {
        int w = 0, h = 0, n = 0;
        sprite[(int)SpriteIndex::none].alpha = nullptr;
        sprite[(int)SpriteIndex::none].center = {0, 0};
        sprite[(int)SpriteIndex::none].size = {0, 0};
        sprite[(int)SpriteIndex::none].number = n;
    }
}