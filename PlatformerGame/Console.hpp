#pragma once

#include <windows.h>
#include <string>
#include "Constant.hpp"
#include "Utility.hpp"
#include "Vec2.hpp"
#include "View.hpp"

class Console {
    HANDLE output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    HWND hWnd = GetConsoleWindow();
    int* alpha_board;
    int* denominator_board;
    char* char_board;
    Vec2<int> size;

public:
    Console();
    Console(HANDLE output_handle, HWND hWnd);
    Vec2<int> get_cursor_pos() const;
    bool set_cursor_pos(Vec2<int> pos) const;
    Vec2<int> get_screen_size() const;
    bool set_screen_size(const Vec2<int>& pos);
    void fix_screen_size() const;
    void unfix_screen_size() const;
    bool hide_cursor() const;
    bool show_cursor() const;
    void set_font_size(int size) const;
    void clear();
    void set_alpha_board(const View& view, const Vec2<int>& rep_pos, const Vec2<int>& rep_size);
    void set_char_board(const std::string& str, int y);
    void set_char_board_from_alpha_board();
    void draw();
};