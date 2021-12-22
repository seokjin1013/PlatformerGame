#include "RoomConstructor.hpp"

using namespace std;

RoomConstructor::RoomConstructor(const Vec2<double>& pos, RoomIndex current_room) : Object(pos) {
    this->current_room = current_room;
}

void RoomConstructor::step() {
    const int stage_size = 100;
    if (current_room == RoomIndex::title) {
        room->add_instance(new Title(Vec2<int>{ 16, 9 } *-6));
    }
    else if (current_room == RoomIndex::stage_selection) {
        room->add_instance(new StageSelection(Vec2<int>{ 16, 9 } *-6));
    }
    else if (current_room == RoomIndex::how_to_play) {
        room->add_instance(new HowToPlay(Vec2<int>{ 16, 9 } *-6));
    }
    else if (current_room == RoomIndex::stage1) {
        int arr[9][66] = {
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,},
            {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,7,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,2,},
            {2,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,2,2,0,2,},
            {2,0,0,0,0,0,6,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,2,0,0,0,0,2,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,2,},
            {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,},
        };
        Vec2<int> player_idx;
        for (int i = 0; i < ssize(arr); i++)
            for (int j = 0; j < ssize(arr[0]); j++)
                if (arr[i][j] == 1)
                    player_idx = { j, i };
        for (int i = 0; i < ssize(arr); i++) {
            for (int j = 0; j < ssize(arr[0]); j++) {
                Vec2<int> pos = (Vec2<int>{ j, i } - player_idx) * 10;
                if (arr[i][j] == 1) room->add_instance(new Player(pos));
                else if (arr[i][j] == 2) room->add_instance(new Block(pos));
                else if (arr[i][j] == 3) room->add_instance(new Key(pos));
                else if (arr[i][j] == 4) room->add_instance(new Battery(pos));
                else if (arr[i][j] == 5) room->add_instance(new Goal(pos, RoomIndex::stage2));
                else if (arr[i][j] == 6) room->add_instance(new Information(pos, SpriteInfo{ SpriteIndex::information_text, 0 }));
                else if (arr[i][j] == 7) room->add_instance(new Information(pos, SpriteInfo{ SpriteIndex::information_text, 1 }));
                else if (arr[i][j] == 8) room->add_instance(new Information(pos, SpriteInfo{ SpriteIndex::information_text, 2 }));
            }
        }
    }
    else if (current_room == RoomIndex::stage2) {
        int arr[16][60] = {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, },
            { 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, },
            { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 2, 0, 0, 0, 0, },
            { 2, 2, 2, 2, 2, 2,12,12, 2, 2, 2, 2, 2,12, 2, 0, 0, 2, 0, 0, 2, 2, 2, 2, 2, 2,12, 2, 2, 2,12, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, },
            { 2, 0, 0, 0, 0, 2,12,12, 2, 0, 0, 0, 2,12, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2,12, 2, 0, 2,12, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 2, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 2,12, 2, 0, 2,12, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 3, 2, 0, 2,12, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 2, 2, 0, 2,12, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2,12, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 2, 0, 0,12, 0, 0, 0,12, 0, 0, 0, 0, 2, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2,12, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2,12, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 2, 0, 0, 0, 0, 0, 0, 0, 0,12, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2,12, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        };
        Vec2<int> player_idx;
        for (int i = 0; i < ssize(arr); i++)
            for (int j = 0; j < ssize(arr[0]); j++)
                if (arr[i][j] == 1)
                    player_idx = { j, i };
        for (int i = 0; i < ssize(arr); i++) {
            for (int j = 0; j < ssize(arr[0]); j++) {
                Vec2<int> pos = (Vec2<int>{ j, i } - player_idx) * 10;
                if (arr[i][j] == 1) room->add_instance(new Player(pos));
                else if (arr[i][j] == 2) room->add_instance(new Block(pos));
                else if (arr[i][j] == 3) room->add_instance(new Key(pos));
                else if (arr[i][j] == 4) room->add_instance(new Battery(pos));
                else if (arr[i][j] == 5) room->add_instance(new Goal(pos, RoomIndex::stage3));
                else if (arr[i][j] == 6) room->add_instance(new Button(pos, false));
                else if (arr[i][j] == 7) room->add_instance(new Button(pos, true));
                else if (arr[i][j] == 8) room->add_instance(new ButtonBlockOn(pos));
                else if (arr[i][j] == 9) room->add_instance(new ButtonBlockOff(pos));
                else if (arr[i][j] == 10) room->add_instance(new LaserBlock(pos, 2));
                else if (arr[i][j] == 11) room->add_instance(new LaserBlock(pos, 0));
                else if (arr[i][j] == 12) room->add_instance(new BreakableBlock(pos));
                else if (arr[i][j] == -1) room->add_instance(new Information(pos, SpriteInfo{ SpriteIndex::information_text, 3 }));
            }
        }
    }
    else if (current_room == RoomIndex::stage3) {
        int arr[16][67] = {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 2,},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 2, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 1, 0, 2,},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 2, 4, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 6, 0, 0, 0, 0, 2,},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 6, 0, 9, 0, 0, 0, 0, 0, 0, 0, 2, 9, 9, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2,},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 2, 0, 9, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 2, 0, 0, 0, 0, 0, 0, 0, 0,},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,-2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0,-3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
            { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,11, 0, 8, 0, 8, 0, 0, 0, 0, 0,10, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2,12, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
            { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
            { 2, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 7, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
            { 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0,13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
            { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0,12,12, 0, 0, 0,12, 0, 0,10, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
            { 0, 0, 0, 0, 0, 0, 2, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
            { 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
        };
        Vec2<int> player_idx;
        for (int i = 0; i < ssize(arr); i++)
            for (int j = 0; j < ssize(arr[0]); j++)
                if (arr[i][j] == 1)
                    player_idx = { j, i };
        for (int i = 0; i < ssize(arr); i++) {
            for (int j = 0; j < ssize(arr[0]); j++) {
                Vec2<int> pos = (Vec2<int>{ j, i } - player_idx) * 10;
                if (arr[i][j] == 1) room->add_instance(new Player(pos));
                else if (arr[i][j] == 2) room->add_instance(new Block(pos));
                else if (arr[i][j] == 3) room->add_instance(new Key(pos));
                else if (arr[i][j] == 4) room->add_instance(new Battery(pos));
                else if (arr[i][j] == 5) room->add_instance(new Goal(pos, RoomIndex::stage4));
                else if (arr[i][j] == 6) room->add_instance(new Button(pos, false));
                else if (arr[i][j] == 7) room->add_instance(new Button(pos, true));
                else if (arr[i][j] == 8) room->add_instance(new ButtonBlockOn(pos));
                else if (arr[i][j] == 9) room->add_instance(new ButtonBlockOff(pos));
                else if (arr[i][j] == 10) room->add_instance(new LaserBlock(pos, 2));
                else if (arr[i][j] == 11) room->add_instance(new LaserBlock(pos, 0));
                else if (arr[i][j] == 12) room->add_instance(new BreakableBlock(pos));
                else if (arr[i][j] == 13) room->add_instance(new LaserBlock(pos, 3));
                else if (arr[i][j] == -1) room->add_instance(new Information(pos, SpriteInfo{ SpriteIndex::information_text, 4 }));
                else if (arr[i][j] == -2) room->add_instance(new Information(pos, SpriteInfo{ SpriteIndex::information_text, 5 }));
                else if (arr[i][j] == -3) room->add_instance(new Information(pos, SpriteInfo{ SpriteIndex::information_text, 6 }));
            }
        }
    }
    else if (current_room == RoomIndex::stage4) {
        int arr[16][60] = {
            { 2, 0, 0, 0, 0, 0,16,16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, },
            { 2, 0, 1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0,16, 0, 0, 0, 0,15, 0, 0, 0, 0,16, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, },
            { 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0,-1, 0, 0, 2, 0, 0, 0, 0, },
            { 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2,15, 2, 0, 0, 0, 0, },
            { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, },
            { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, },
            { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, },
            { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, },
            { 0, 0, 0, 0, 0, 0, 2, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 0, 0, },
            { 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0,15, 0, 0, 0,15, 0, 0, 0,15, 0, 0, 0,15, 0, 0, 0,15,15,15,15,15,15, 2, 0, 0, 0, 0, },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        };
        Vec2<int> player_idx;
        for (int i = 0; i < ssize(arr); i++)
            for (int j = 0; j < ssize(arr[0]); j++)
                if (arr[i][j] == 1)
                    player_idx = { j, i };
        for (int i = 0; i < ssize(arr); i++) {
            for (int j = 0; j < ssize(arr[0]); j++) {
                Vec2<int> pos = (Vec2<int>{ j, i } - player_idx) * 10;
                if (arr[i][j] == 1) room->add_instance(new Player(pos));
                else if (arr[i][j] == 2) room->add_instance(new Block(pos));
                else if (arr[i][j] == 3) room->add_instance(new Key(pos));
                else if (arr[i][j] == 4) room->add_instance(new Battery(pos));
                else if (arr[i][j] == 5) room->add_instance(new Goal(pos, RoomIndex::stage5));
                else if (arr[i][j] == 6) room->add_instance(new Button(pos, false));
                else if (arr[i][j] == 7) room->add_instance(new Button(pos, true));
                else if (arr[i][j] == 8) room->add_instance(new ButtonBlockOn(pos));
                else if (arr[i][j] == 9) room->add_instance(new ButtonBlockOff(pos));
                else if (arr[i][j] == 10) room->add_instance(new LaserBlock(pos, 2));
                else if (arr[i][j] == 11) room->add_instance(new LaserBlock(pos, 0));
                else if (arr[i][j] == 12) room->add_instance(new BreakableBlock(pos));
                else if (arr[i][j] == 13) room->add_instance(new BulletBlock(pos, 2));
                else if (arr[i][j] == 14) room->add_instance(new BulletBlock(pos, 0));
                else if (arr[i][j] == 15) room->add_instance(new FlickingBlockOn(pos));
                else if (arr[i][j] == 16) room->add_instance(new FlickingBlockOff(pos));
                else if (arr[i][j] == -1) room->add_instance(new Information(pos, SpriteInfo{ SpriteIndex::information_text, 7 }));
            }
        }
    }
    else if (current_room == RoomIndex::stage5) {
        int arr[16][60] = {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,13, 0, 2, 0, 0, 0, 0, 0,13, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,13, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0,13, 0, 2, 0, 0, 0, 0, 0,13, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,13, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,13, 0, 2, 0, 0, 0, 0, 0,13, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,13, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,13, 0, 2, 0, 0, 0, 0, 0,13, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,13, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 2, 2,12,12,12, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 2, 0, 0, 0, 0, 0, 0,-1, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 5, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,12, 0,13, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 0, 0, 0, 0, 0, 0, 0, 0,14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,13, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
            { 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        };
        Vec2<int> player_idx;
        for (int i = 0; i < ssize(arr); i++)
            for (int j = 0; j < ssize(arr[0]); j++)
                if (arr[i][j] == 1)
                    player_idx = { j, i };
        for (int i = 0; i < ssize(arr); i++) {
            for (int j = 0; j < ssize(arr[0]); j++) {
                Vec2<int> pos = (Vec2<int>{ j, i } - player_idx) * 10;
                if (arr[i][j] == 1) room->add_instance(new Player(pos));
                else if (arr[i][j] == 2) room->add_instance(new Block(pos));
                else if (arr[i][j] == 3) room->add_instance(new Key(pos));
                else if (arr[i][j] == 4) room->add_instance(new Battery(pos));
                else if (arr[i][j] == 5) room->add_instance(new Goal(pos, RoomIndex::stage_selection));
                else if (arr[i][j] == 6) room->add_instance(new Button(pos, false));
                else if (arr[i][j] == 7) room->add_instance(new Button(pos, true));
                else if (arr[i][j] == 8) room->add_instance(new ButtonBlockOn(pos));
                else if (arr[i][j] == 9) room->add_instance(new ButtonBlockOff(pos));
                else if (arr[i][j] == 10) room->add_instance(new LaserBlock(pos, 2));
                else if (arr[i][j] == 11) room->add_instance(new LaserBlock(pos, 0));
                else if (arr[i][j] == 12) room->add_instance(new BreakableBlock(pos));
                else if (arr[i][j] == 13) room->add_instance(new BulletBlock(pos, 2));
                else if (arr[i][j] == 14) room->add_instance(new BulletBlock(pos, 0));
                else if (arr[i][j] == 15) room->add_instance(new FlickingBlockOn(pos));
                else if (arr[i][j] == 16) room->add_instance(new FlickingBlockOff(pos));
                else if (arr[i][j] == -1) room->add_instance(new Information(pos, SpriteInfo{ SpriteIndex::information_text, 8 }));
            }
        }
    }
    else if (current_room == RoomIndex::stage11) {
        int arr[30][60] = {
                   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                   {1,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,1},
                   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                   {1,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,1},
                   {1,12,12,12,12,12,12,12,12,-1,12,12,12,12,12,12,12,12,1},
                   {1,12,12,12,12,12,12,12,12,1,12,12,12,12,12,12,12,12,1},
                   {1,12,12,12,12,12,12,12,12,1,12,12,12,12,12,12,12,12,1},
                   {1,12,12,12,12,12,12,12,12,1,12,12,12,12,12,12,12,12,1},
                   {1,12,12,12,12,12,12,12,12,1,14,14,14,14,14,14,14,14,1},
                   {1,12,12,12,12,12,12,12,12,1,12,12,12,12,12,12,12,12,1},
                   {7,10,12,12,4,12,12,12,12,1,12,12,12,12,12,12,12,12,1},
                   {7,10,0,0,4,12,12,12,12,1,12,12,12,12,12,12,12,12,1},
                   {7,10,0,0,4,12,12,12,5,1,12,12,12,12,12,12,12,12,1},
                   {7,10,0,0,4,12,12,12,1,1,12,12,12,12,12,12,12,12,1},
                   {7,10,0,0,4,12,12,12,12,1,14,14,14,14,14,14,14,14,1},
                   {7,10,0,0,4,12,12,12,12,1,12,12,12,12,1,12,12,12,1},
                   {7,10,0,2,4,12,0,12,9,1,12,5,12,12,1,12,12,6,1},
                   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        };
        Vec2<int> player_idx;
        for (int i = 0; i < ssize(arr); i++)
            for (int j = 0; j < ssize(arr[0]); j++)
                if (arr[i][j] == -1)
                    player_idx = { j, i };
        for (int i = 0; i < ssize(arr); i++) {
            for (int j = 0; j < ssize(arr[0]); j++) {
                Vec2<int> pos = (Vec2<int>{ j, i } - player_idx) * 10;
                if (arr[i][j] == -1) room->add_instance(new Player(pos));
                else if (arr[i][j] == 1) room->add_instance(new Block(pos));
                else if (arr[i][j] == 2) room->add_instance(new Goal(pos, RoomIndex::stage12));
                else if (arr[i][j] == 3) room->add_instance(new BulletBlock(pos, 1));
                else if (arr[i][j] == 4) room->add_instance(new BulletBlock(pos, 0));
                else if (arr[i][j] == 5) room->add_instance(new Battery(pos));
                else if (arr[i][j] == 6) room->add_instance(new Key(pos));
                else if (arr[i][j] == 7) room->add_instance(new LaserBlock(pos, 0));
                else if (arr[i][j] == 8) room->add_instance(new LaserBlock(pos, 1));
                else if (arr[i][j] == 9) room->add_instance(new Button(pos, 0));
                else if (arr[i][j] == 10) room->add_instance(new ButtonBlockOff(pos));
                else if (arr[i][j] == 11) room->add_instance(new ButtonBlockOn(pos));
                else if (arr[i][j] == 12) room->add_instance(new FlickingBlockOff(pos));
                else if (arr[i][j] == 13) room->add_instance(new FlickingBlockOn(pos));
                else if (arr[i][j] == 14)room->add_instance(new BreakableBlock(pos));
            }
        }
    }
    else if (current_room == RoomIndex::stage12) {
        int arr[30][60] = {
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                {1,4,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,3,1},
                {1,4,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1},
                {1,4,13,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1},
                {1,4,13,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1},
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1},
                {1,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,0,0,0,1},
                {1,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
                {1,4,0,0,0,0,0,0,0,0,0,0,12,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0,0,0,0,1},
                {1,9,0,0,0,12,0,0,13,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1},
                {1,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,1},
                {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,1,1},
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        };
        Vec2<int> player_idx;
        for (int i = 0; i < ssize(arr); i++)
            for (int j = 0; j < ssize(arr[0]); j++)
                if (arr[i][j] == -1)
                    player_idx = { j, i };
        for (int i = 0; i < ssize(arr); i++) {
            for (int j = 0; j < ssize(arr[0]); j++) {
                Vec2<int> pos = (Vec2<int>{ j, i } - player_idx) * 10;
                if (arr[i][j] == -1) room->add_instance(new Player(pos));
                else if (arr[i][j] == 1) room->add_instance(new Block(pos));
                else if (arr[i][j] == 2) room->add_instance(new Goal(pos, RoomIndex::stage13));
                else if (arr[i][j] == 3) room->add_instance(new BulletBlock(pos, 2));
                else if (arr[i][j] == 4) room->add_instance(new BulletBlock(pos, 0));
                else if (arr[i][j] == 5) room->add_instance(new Battery(pos));
                else if (arr[i][j] == 6) room->add_instance(new Key(pos));
                else if (arr[i][j] == 7) room->add_instance(new LaserBlock(pos, 2));
                else if (arr[i][j] == 8) room->add_instance(new LaserBlock(pos, 0));
                else if (arr[i][j] == 9) room->add_instance(new Button(pos, 0));
                else if (arr[i][j] == 10) room->add_instance(new ButtonBlockOff(pos));
                else if (arr[i][j] == 11) room->add_instance(new ButtonBlockOn(pos));
                else if (arr[i][j] == 12) room->add_instance(new FlickingBlockOff(pos));
                else if (arr[i][j] == 13) room->add_instance(new FlickingBlockOn(pos));
            }
        }
    }
    else if (current_room == RoomIndex::stage13) {
        int arr[30][60] = {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
            {0,0,0,0,9,0,0,0,9,0,0,0,9,0,0,6,2,1,0,0},
            {0,0,0,0,0,9,0,0,0,9,0,0,0,9,0,0,0,1,0,0},
            {0,0,0,1,10,10,10,10,10,10,10,10,10,10,10,10,10,1,0,0},
            {0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
            {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,9,5,1},
            {1,0,1,1,0,14,14,14,14,14,14,14,14,14,14,14,14,1,1,1},
            {1,0,0,11,-1,12,12,13,13,12,12,13,13,12,12,13,13,1,0,0},
            {1,1,1,1,1,7,7,7,7,7,7,7,7,7,7,7,7,1},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
        };
        Vec2<int> player_idx;
        for (int i = 0; i < ssize(arr); i++)
            for (int j = 0; j < ssize(arr[0]); j++)
                if (arr[i][j] == -1)
                    player_idx = { j, i };
        for (int i = 0; i < ssize(arr); i++) {
            for (int j = 0; j < ssize(arr[0]); j++) {
                Vec2<int> pos = (Vec2<int>{ j, i } - player_idx) * 10;
                if (arr[i][j] == -1) room->add_instance(new Player(pos));
                else if (arr[i][j] == 1) room->add_instance(new Block(pos));
                else if (arr[i][j] == 2) room->add_instance(new Goal(pos, RoomIndex::stage14));
                else if (arr[i][j] == 5) room->add_instance(new Battery(pos));
                else if (arr[i][j] == 6) room->add_instance(new Key(pos));
                else if (arr[i][j] == 7) room->add_instance(new LaserBlock(pos, 3));
                else if (arr[i][j] == 9) room->add_instance(new Button(pos, 0));
                else if (arr[i][j] == 10) room->add_instance(new ButtonBlockOff(pos));
                else if (arr[i][j] == 11) room->add_instance(new ButtonBlockOn(pos));
                else if (arr[i][j] == 12) room->add_instance(new FlickingBlockOff(pos));
                else if (arr[i][j] == 13) room->add_instance(new FlickingBlockOn(pos));
                else if (arr[i][j] == 14)room->add_instance(new BreakableBlock(pos));
            }
        }
    }
    else if (current_room == RoomIndex::stage14) {
        int arr[30][60] = {
            {1,1,1,1,1,1,1,1,1,3,3,1,1,3,3,1,1,1,1},
            {1,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1},
            {1,3,0,0,0,13,0,0,1,1,3,16,16,1,1,3,1,1,1},
            {1,0,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,1},
            {1,0,0,0,15,0,0,0,15,0,0,0,4,15,0,0,0,4,1},
            {1,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,16,1,1,1,1,1,1,1,1,16,1,1,1,1,16,0,0,1},
            {1,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0,0,1},
            {1,13,13,1,1,12,1,1,1,12,1,13,13,1,12,12,1,11,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
            {1,0,-1,0,14,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {1,14,14,14,0,14,14,0,14,0,14,14,14,14,0,14,14,14,14},
            {0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,5,0,0,0,0,14,0,0,14,0,0,0,0,0}
        };
        Vec2<int> player_idx;
        for (int i = 0; i < ssize(arr); i++)
            for (int j = 0; j < ssize(arr[0]); j++)
                if (arr[i][j] == -1)
                    player_idx = { j, i };
        for (int i = 0; i < ssize(arr); i++) {
            for (int j = 0; j < ssize(arr[0]); j++) {
                Vec2<int> pos = (Vec2<int>{ j, i } - player_idx) * 10;
                if (arr[i][j] == -1) room->add_instance(new Player(pos));
                else if (arr[i][j] == 1) room->add_instance(new Block(pos));
                else if (arr[i][j] == 2) room->add_instance(new Goal(pos, RoomIndex::stage15));
                else if (arr[i][j] == 3) room->add_instance(new BulletBlock(pos, 1));
                else if (arr[i][j] == 4) room->add_instance(new BulletBlock(pos, 2));
                else if (arr[i][j] == 15) room->add_instance(new BulletBlock(pos, 0));
                else if (arr[i][j] == 16) room->add_instance(new BulletBlock(pos, 3));
                else if (arr[i][j] == 5) room->add_instance(new Battery(pos));
                else if (arr[i][j] == 6) room->add_instance(new Key(pos));
                else if (arr[i][j] == 7) room->add_instance(new LaserBlock(pos, 0));
                else if (arr[i][j] == 8) room->add_instance(new LaserBlock(pos, 1));
                else if (arr[i][j] == 9) room->add_instance(new Button(pos, 0));
                else if (arr[i][j] == 10) room->add_instance(new ButtonBlockOff(pos));
                else if (arr[i][j] == 11) room->add_instance(new ButtonBlockOn(pos));
                else if (arr[i][j] == 12) room->add_instance(new FlickingBlockOff(pos));
                else if (arr[i][j] == 13) room->add_instance(new FlickingBlockOn(pos));
                else if (arr[i][j] == 14)room->add_instance(new BreakableBlock(pos));
            }
        }
    }
    else if (current_room == RoomIndex::stage15) {
        int arr[30][60] = {
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                {1,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,13,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,3,0,1},
                {1,0,0,4,0,0,0,0,9,-1,9,0,0,0,0,0,0,3,1},
                {1,0,0,4,0,0,0,0,0,14,0,0,0,0,3,0,0,0,1},
                {1,0,4,0,0,0,0,0,9,14,9,0,0,3,0,0,0,0,1},
                {1,4,0,0,0,0,0,0,0,14,0,0,0,0,0,3,0,0,1},
                {1,0,0,4,0,0,0,0,9,14,9,0,0,0,0,0,0,3,1},
                {1,0,0,4,0,0,0,0,0,14,0,0,0,0,0,3,0,0,1},
                {1,0,0,0,4,0,0,0,9,14,9,0,0,0,0,0,3,0,1},
                {1,0,4,0,0,0,0,0,0,14,0,0,0,0,0,0,0,3,1},
                {1,0,0,4,0,0,0,0,9,14,9,0,0,0,3,0,0,0,1},
                {1,4,0,0,0,0,0,0,0,14,0,0,0,0,0,0,3,0,1},
                {1,0,0,0,0,0,10,5,1,6,1,5,11,0,0,0,0,0,3,1},
                {1,1,1,1,1,1,7,1,1,2,1,1,7,1,1,1,1,1,1,1},
        };
        Vec2<int> player_idx;
        for (int i = 0; i < ssize(arr); i++)
            for (int j = 0; j < ssize(arr[0]); j++)
                if (arr[i][j] == -1)
                    player_idx = { j, i };
        for (int i = 0; i < ssize(arr); i++) {
            for (int j = 0; j < ssize(arr[0]); j++) {
                Vec2<int> pos = (Vec2<int>{ j, i } - player_idx) * 10;
                if (arr[i][j] == -1) room->add_instance(new Player(pos));
                else if (arr[i][j] == 1) room->add_instance(new Block(pos));
                else if (arr[i][j] == 2) room->add_instance(new Goal(pos, RoomIndex::stage_selection));
                else if (arr[i][j] == 3) room->add_instance(new BulletBlock(pos, 2));
                else if (arr[i][j] == 4) room->add_instance(new BulletBlock(pos, 0));
                else if (arr[i][j] == 5) room->add_instance(new Battery(pos));
                else if (arr[i][j] == 6) room->add_instance(new Key(pos));
                else if (arr[i][j] == 7) room->add_instance(new LaserBlock(pos, 3));
                else if (arr[i][j] == 8) room->add_instance(new LaserBlock(pos, 1));
                else if (arr[i][j] == 9) room->add_instance(new Button(pos, 0));
                else if (arr[i][j] == 10) room->add_instance(new ButtonBlockOff(pos));
                else if (arr[i][j] == 11) room->add_instance(new ButtonBlockOn(pos));
                else if (arr[i][j] == 12) room->add_instance(new FlickingBlockOff(pos));
                else if (arr[i][j] == 13) room->add_instance(new FlickingBlockOn(pos));
                else if (arr[i][j] == 14)room->add_instance(new BreakableBlock(pos));
            }
        }
    }
    room->del_instance(this);
}