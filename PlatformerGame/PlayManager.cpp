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
    console.set_screen_size(Vec2<int>{ 16, 9 } * 12);
    console.fix_screen_size();
    View view;

    while (true) {
        Room room(Vec2<int>{ 16, 9 } * 12);
        if (current_room == 0) {
            room.add_instance(new Player({ 0, 0 }));
            for (int i = -30; i <= 3; ++i)
                room.add_instance(new Block({ i * 10.0, 30 }));
            room.add_instance(new Button({ -10, 20 }, true));
            room.add_instance(new Button({ -30, 20 }, false));
            room.add_instance(new Button({ -50, 10 }, true));
            room.add_instance(new Button({ -70, 0 }, false));
            room.add_instance(new ButtonBlockOn({ -70, 20 }));
            room.add_instance(new ButtonBlockOn({ -80, 20 }));
            room.add_instance(new ButtonBlockOn({ -90, 20 }));
            room.add_instance(new ButtonBlockOff({ -60, 20 }));
            room.add_instance(new Key({ 20, 20 }));
            room.add_instance(new Goal({ 20, 20 }, 1));
            room.add_instance(new Block({ 10, 0 }));
            room.add_instance(new Block({ 70, 0 }));
            room.add_instance(new Block({ 40, 25 }));
            room.add_instance(new Block({ 40, -25 }));
            room.add_instance(new BulletBlock({ 30, 0 }, 2));
            room.add_instance(new BulletBlock({ 40, 5 }, 1));
            room.add_instance(new BulletBlock({ 50, 0 }, 0));
            room.add_instance(new BulletBlock({ 40, -5 }, 3));
        }
        else if (current_room == 1) {
            room.add_instance(new Player({120, -60 }));
            int arr[40][40] = {
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                {1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                {1,1,1,0,0,0,1,1,1,0,4,0,1,0,5,0,1,0,4,0,1,1,1,1},
                {1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,1,2,0,0,0,0,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1},
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            };
            for (int i = 0; i < ssize(arr); i++) {
                for (int j = 0; j < ssize(arr[0]); j++) {
                    if (arr[i][j] == 1) room.add_instance(new Block({ -100.0 + j * 10.0, -100 + i * 10.0 }));
                    if (arr[i][j] == 2) room.add_instance(new Goal({ -100.0 + j * 10.0, -100 + i * 10.0 }, 2));
                    if (arr[i][j] == 3) room.add_instance(new BulletBlock({ -100.0 + j * 10.0, -100 + i * 10.0 }, 0));
                    if (arr[i][j] == 4) room.add_instance(new Battery({ -100.0 + j * 10.0, -100 + i * 10.0 }));
                    if (arr[i][j] == 5) room.add_instance(new Key({ -100.0 + j * 10.0, -100 + i * 10.0 }));
                }
            }
        }
        else if (current_room == 2)
        {
            room.add_instance(new Player({ 100, 20 }));
            int arr[40][40] = {
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
                {1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,1,1,1,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,1,0,0,0,0,0,0,5,1},
                {1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,1,0,0,0,1,0,1,1,1},
                {1,4,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,6,0,0,0,0,0,0,1},
                {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,1,1,1,1,1,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
                {1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,1,0,0,0,1,0,1,1,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,6,0,0,1,0,0,0,1},
                {1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}

            };
            for (int i = 0; i < ssize(arr); i++) {
                for (int j = 0; j < ssize(arr[0]); j++) {
                    if (arr[i][j] == 1) room.add_instance(new Block({ -100.0 + j * 10.0, -100 + i * 10.0 }));
                    if (arr[i][j] == 2) room.add_instance(new Goal({ -100.0 + j * 10.0, -100 + i * 10.0 }, 3));
                    if (arr[i][j] == 6) room.add_instance(new BulletBlock({ -100.0 + j * 10.0, -100 + i * 10.0 }, 0));
                    if (arr[i][j] == 7) room.add_instance(new BulletBlock({ -100.0 + j * 10.0, -100 + i * 10.0 }, 2));
                    if (arr[i][j] == 4) room.add_instance(new Battery({ -100.0 + j * 10.0, -100 + i * 10.0 }));
                    if (arr[i][j] == 5) room.add_instance(new Key({ -100.0 + j * 10.0, -100 + i * 10.0 }));
                }
            }
        }
        else if (current_room == 2)
        {
            room.add_instance(new Player({ 100, 20 }));
            int arr[40][40] = {
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
                {1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,1,1,1,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,1,0,0,0,0,0,0,5,1},
                {1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,1,0,0,0,1,0,1,1,1},
                {1,4,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,3,0,0,0,0,0,0,1},
                {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,1,1,1,1,1,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
                {1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,1,0,0,0,1,0,1,1,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,3,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}

            };
            for (int i = 0; i < ssize(arr); i++) {
                for (int j = 0; j < ssize(arr[0]); j++) {
                    if (arr[i][j] == 1) room.add_instance(new Block({ -100.0 + j * 10.0, -100 + i * 10.0 }));
                    if (arr[i][j] == 2) room.add_instance(new Goal({ -100.0 + j * 10.0, -100 + i * 10.0 }, 3));
                    if (arr[i][j] == 3) room.add_instance(new BulletBlock({ -100.0 + j * 10.0, -100 + i * 10.0 }, 2));
                    if (arr[i][j] == 4) room.add_instance(new Battery({ -100.0 + j * 10.0, -100 + i * 10.0 }));
                    if (arr[i][j] == 5) room.add_instance(new Key({ -100.0 + j * 10.0, -100 + i * 10.0 }));
                }
            }
        }
        else if (current_room == 3)
        {
            room.add_instance(new Player({ 60, 10 }));
            int arr[35][35] = {
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, // 35
                {1,3,0,0,0,0,0,0,0,4,1,0,0,0,0,0,0,0,1},
                {1,3,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,2,1},
                {1,3,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1},
                {1,3,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
                {1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1},
                {1,5,0,0,0,1,0,0,0,0,0,0,0,0,1,1,0,0,1},
                {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1},
                {1,0,0,1,3,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1},
                {1,0,0,0,0,1,3,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},        // 미는 블록
                {1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,3,1,0,0,0,0,0,0,1},        // 총알이 반대로 나갈 수 있다면
                {1,3,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
                {1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,3,1,0,0,0,0,0,0,1},        // 얘도
                {1,3,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
                {1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
                {1,0,0,0,0,4,0,0,0,0,0,1,1,0,0,0,0,0,1},        // 버튼
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
            };
            for (int i = 0; i < ssize(arr); i++) {
                for (int j = 0; j < ssize(arr[0]); j++) {
                    if (arr[i][j] == 1) room.add_instance(new Block({ -100.0 + j * 10.0, -100 + i * 10.0 }));
                    if (arr[i][j] == 2) room.add_instance(new Goal({ -100.0 + j * 10.0, -100 + i * 10.0 }, 4));
                    if (arr[i][j] == 3) room.add_instance(new BulletBlock({ -100.0 + j * 10.0, -100 + i * 10.0 }, 2));
                    if (arr[i][j] == 4) room.add_instance(new Battery({ -100.0 + j * 10.0, -100 + i * 10.0 }));
                    if (arr[i][j] == 5) room.add_instance(new Key({ -100.0 + j * 10.0, -100 + i * 10.0 }));
                }
            }
        }
        else if (current_room == 4)
        {
            room.add_instance(new Player({ 120, 10 }));
            int arr[40][40] = {
                {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
                {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,1,0,0,0,0,0,0,5,1},
                {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
                {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,0},
                {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0},
                {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0},
                {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0},
                {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
                {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,2,1,0,0,0,0,0,0,0,0,0,0},
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0}
            };
            for (int i = 0; i < ssize(arr); i++) {
                for (int j = 0; j < ssize(arr[0]); j++) {
                    if (arr[i][j] == 1) room.add_instance(new Block({ -100.0 + j * 10.0, -100 + i * 10.0 }));
                    if (arr[i][j] == 2) room.add_instance(new Goal({ -100.0 + j * 10.0, -100 + i * 10.0 }, 5));
                    if (arr[i][j] == 3) room.add_instance(new BulletBlock({ -100.0 + j * 10.0, -100 + i * 10.0 }, 2));
                    if (arr[i][j] == 4) room.add_instance(new Battery({ -100.0 + j * 10.0, -100 + i * 10.0 }));
                    if (arr[i][j] == 5) room.add_instance(new Key({ -100.0 + j * 10.0, -100 + i * 10.0 }));
                }
            }
        }
        else if (current_room == 5)
        {

            room.add_instance(new Player({ 0, -50 }));
            int arr[20][60] = {
                {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0}, // 35
                {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,1,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0},
                {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0},
                {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,6,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},    // 잠금 버튼을 누르면 6번이 열리게 
                {0,0,0,1,2,5,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
                {0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
                {0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,2,0,0,0,0,1,0,0,0,0,0,0,0,0,0,4,0,0,1,0},    // 잠금버튼(4)
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
            };
            for (int i = 0; i < ssize(arr); i++) {
                for (int j = 0; j < ssize(arr[0]); j++) {
                    if (arr[i][j] == 1) room.add_instance(new Block({ -100.0 + j * 10.0, -100 + i * 10.0 }));
                    if (arr[i][j] == 2) room.add_instance(new Goal({ -100.0 + j * 10.0, -100 + i * 10.0 }, 6));
                    if (arr[i][j] == 3) room.add_instance(new BulletBlock({ -100.0 + j * 10.0, -100 + i * 10.0 }, 2));
                    if (arr[i][j] == 4) room.add_instance(new Battery({ -100.0 + j * 10.0, -100 + i * 10.0 }));
                    if (arr[i][j] == 5) room.add_instance(new Key({ -100.0 + j * 10.0, -100 + i * 10.0 }));
                }
            }
        }
        else if (current_room == 6)
        {
            room.add_instance(new Player({ 0, 70 }));
            int arr[30][60] = {
                {0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
                {0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0},
                {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,0,0},
                {0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0},
                {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,5,0,0,1,0,0},  // 5번을 획득(OR) 어떤 방법으로 버튼을 누르면 6번이 열리게
                {0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0},
                {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1},
                {1,0,0,0,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
                {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
                {1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1},
                {0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0},
                {0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0},
                {0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0},
                {0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0},
                {0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0},
                {0,0,0,0,1,1,0,0,0,6,0,0,0,0,0,0,0,0,1,1,0,0,0,0},  // 여기 6번이 열림
                {0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0}
            };
            for (int i = 0; i < ssize(arr); i++) {
                for (int j = 0; j < ssize(arr[0]); j++) {
                    if (arr[i][j] == 1) room.add_instance(new Block({ -100.0 + j * 10.0, -100 + i * 10.0 }));
                    if (arr[i][j] == 2) room.add_instance(new Goal({ -100.0 + j * 10.0, -100 + i * 10.0 }, 7));
                    if (arr[i][j] == 3) room.add_instance(new BulletBlock({ -100.0 + j * 10.0, -100 + i * 10.0 }, 2));
                    if (arr[i][j] == 4) room.add_instance(new Battery({ -100.0 + j * 10.0, -100 + i * 10.0 }));
                    if (arr[i][j] == 5) room.add_instance(new Key({ -100.0 + j * 10.0, -100 + i * 10.0 }));
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