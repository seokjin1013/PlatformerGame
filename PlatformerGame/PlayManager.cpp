#include "PlayManager.hpp"

using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;

PlayManager& PlayManager::instance() {
    static PlayManager instance;
    return instance;
}

void PlayManager::play() {
    Console console;
    console.hide_cursor();
    console.set_font_size(8);
    console.set_screen_size(Vec2<int>{16, 9} *12);
    console.fix_screen_size();
    View view;

    while (true) {
        Room room(Vec2<int>{16, 9} *12);
        if (current_room == 0) {
            new Player(&room, { 30, -20 });
            int arr[40][40] = {
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                {1,3,0,0,0,0,0,0,0,0,0,0,0,5,0,1},
                {1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,1,1,0,1,1,1,0,1,1,1,0,0,0,0,1},
                {1,1,1,0,1,1,1,0,1,1,1,1,0,0,1,1},
                {1,1,1,0,1,1,1,0,1,1,1,0,0,0,0,1},
                {1,1,1,0,1,1,1,0,1,1,1,0,0,1,0,1},
                {1,1,1,0,1,1,1,0,1,1,1,1,0,0,0,1},
                {1,1,1,4,1,1,1,4,1,1,1,0,0,0,1,1},
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            };
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 16; j++) {
                    if (arr[i][j] == 1) new Block(&room, Vec2<double>{-100.0 + j * 10.0, -100 + i * 10.0});
                    if (arr[i][j] == 2) new Goal(&room, Vec2<double>{-100.0 + j * 10.0, -100 + i * 10.0}, 1);
                    if (arr[i][j] == 3) new Bullet_shooter(&room, Vec2<double>{-100.0 + j * 10.0, -100 + i * 10.0});
                    if (arr[i][j] == 4) new Battery(&room, Vec2<double>{-100.0 + j * 10.0, -100 + i * 10.0});
                    if (arr[i][j] == 5) new Key(&room, Vec2<double>{-100.0 + j * 10.0, -100 + i * 10.0});
                }
            }
        }
        else if (current_room == 1) {
            new Player(&room, {120, -60 });
            int arr[40][40] = {
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                {1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                {1,1,1,0,0,0,1,1,1,0,4,0,1,0,5,0,1,0,4,0,1,1,1,1},
                {1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,1,2,0,0,0,0,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1},
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            };
            for (int i = 0; i < size(arr); i++) {
                for (int j = 0; j < size(arr[0]); j++) {
                    if (arr[i][j] == 1) new Block(&room, Vec2<double>{-100.0 + j * 10.0, -100 + i * 10.0});
                    if (arr[i][j] == 2) new Goal(&room, Vec2<double>{-100.0 + j * 10.0, -100 + i * 10.0}, 1);
                    if (arr[i][j] == 3) new Bullet_shooter(&room, Vec2<double>{-100.0 + j * 10.0, -100 + i * 10.0});
                    if (arr[i][j] == 4) new Battery(&room, Vec2<double>{-100.0 + j * 10.0, -100 + i * 10.0});
                    if (arr[i][j] == 5) new Key(&room, Vec2<double>{-100.0 + j * 10.0, -100 + i * 10.0});
                }
            }
        }
        restart_room = false;
        while (true) {
            Controller::instance().step();
            room.step();
            if (restart_room) break;
            str.emplace_back("frame_stacked");
            if (!frame_skip_or_waiting()) {
                view.clear();
                view.draw(room);
                console.clear();
                console.set_alpha_board(view, { 0, 0 }, Vec2<int>{16, 9} *12);
                console.set_char_board_from_alpha_board();
                str.emplace_back("fps : " + to_string(fps));
                str.emplace_back("fps_real : " + to_string(fps_real));
                str.emplace_back("delayed_time : " + to_string(delayed_time.count()));
                for (int i = 0; i < ssize(str); ++i)
                    console.set_char_board(str[i], i);
                str.clear();
                console.draw();
            }
        }
    }
}

void PlayManager::set_room(int room) {
    current_room = room;
    restart_room = true;
}

int PlayManager::get_room() {
    return current_room;
}

PlayManager::PlayManager() {
    previous_time = high_resolution_clock::now();
    previous_time_real = high_resolution_clock::now();
    delayed_time = 0s;
}

bool PlayManager::frame_skip_or_waiting() {
    auto current_time = high_resolution_clock::now();
    auto second_per_frame = 1000ms / fps_standard;
    delayed_time += duration<double, milli>(current_time - previous_time) - second_per_frame;

    fps = 1000 / duration<double, milli>(current_time - previous_time).count();
    fps_real = 1000 / duration<double, milli>(current_time - previous_time_real).count();

    previous_time = high_resolution_clock::now();
    if (delayed_time > second_per_frame * 2) return true;
    if (delayed_time < 0ms) this_thread::sleep_for(-delayed_time);
    previous_time_real = high_resolution_clock::now();
    return false;
}