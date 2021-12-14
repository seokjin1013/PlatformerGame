#include "Console.hpp"

using namespace std;

Console::Console() {
    alpha_board = new int[MAX_RESOLUTION.area()];
    denominator_board = new int[MAX_RESOLUTION.area()];
    char_board = new char[MAX_RESOLUTION.area()];
    memset(alpha_board, 0, MAX_RESOLUTION.area() * sizeof(int));
    memset(denominator_board, 0, MAX_RESOLUTION.area() * sizeof(int));
    memset(char_board, 0, MAX_RESOLUTION.area() * sizeof(char));
}

Console::Console(HANDLE output_handle, HWND hWnd) : Console() {
    this->output_handle = output_handle;
    this->hWnd = hWnd;
}

Vec2<int> Console::get_cursor_pos() const {
    CONSOLE_SCREEN_BUFFER_INFO buffer;
    GetConsoleScreenBufferInfo(output_handle, &buffer);
    return Vec2<int>{buffer.dwCursorPosition.X / 2, buffer.dwCursorPosition.Y};
}

bool Console::set_cursor_pos(Vec2<int> pos) const {
    return SetConsoleCursorPosition(output_handle, {short(pos.x * 2), short(pos.y)});
}

Vec2<int> Console::get_screen_size() const {
    return size;
}

bool Console::set_screen_size(const Vec2<int>& pos) {
    size = pos;
    size.x *= 2;
    string command;
    command += "mode con:cols=";
    command += to_string(size.x);
    command += " lines=";
    command += to_string(size.y);
    return system(command.c_str()) == 0;
}

void Console::fix_screen_size() const {
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

void Console::unfix_screen_size() const {
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) | WS_MAXIMIZEBOX | WS_SIZEBOX);
}

bool Console::hide_cursor() const {
    const char* const virt = "\033[?25l";
    fwrite(virt, sizeof(char), strlen(virt), stdout);
    return true;
    //CONSOLE_CURSOR_INFO info;
    //if (!GetConsoleCursorInfo(output_handle, &info)) return false;
    //info.bVisible = 0;
    //if (!SetConsoleCursorInfo(output_handle, &info)) return false;
    //return true;
}

bool Console::show_cursor() const {
    const char* const virt = "\033[?25h";
    fwrite(virt, sizeof(char), strlen(virt), stdout);
    return true;
    //CONSOLE_CURSOR_INFO info;
    //if (!GetConsoleCursorInfo(output_handle, &info)) return false;
    //info.bVisible = 1;
    //if (!SetConsoleCursorInfo(output_handle, &info)) return false;
    //return true;
}

void Console::set_font_size(int size) const {
    HANDLE hcsb = CreateFileA("CONOUT$", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL, NULL);
    CONSOLE_FONT_INFOEX cfi = {sizeof(cfi)};
    GetCurrentConsoleFontEx(hcsb, FALSE, &cfi);
    cfi.dwFontSize = COORD{1, short(size)};
    SetCurrentConsoleFontEx(hcsb, FALSE, &cfi);
}

void Console::clear() {
    memset(alpha_board, 0, MAX_RESOLUTION.area() * sizeof(int));
    memset(char_board, 0, MAX_RESOLUTION.area() * sizeof(char));
}

void Console::set_alpha_board(const View& view, const Vec2<int>& rep_pos, const Vec2<int>& rep_size) {
    const int* const view_alpha_board = view.get_alpha_board();
    const auto& view_size = view.get_size();
    if ((rep_size.x * 2) < view_size.x && rep_size.y < view_size.y) {
        for (int i = 0; i < rep_size.y; ++i)
            for (int j = 0; j < (rep_size.x * 2); ++j) {
                int num = 0, den = 0;
                int ks = static_cast<int>(i * view_size.y / rep_size.y), ke = static_cast<int>((i + 1) * view_size.y / rep_size.y);
                int ls = static_cast<int>(j * view_size.x / (rep_size.x * 2)), le = static_cast<int>((j + 1) * view_size.x / (rep_size.x * 2));
                for (int k = ks; k < ke; ++k)
                    for (int l = ls; l < le; ++l) {
                        num += view_alpha_board[utility::get_index(view_size, k, l)];
                        ++den;
                    }
                alpha_board[utility::get_index(size, rep_pos + Vec2<int>{j, i})] = num / den;
            }
    }
    if ((rep_size.x * 2) >= view_size.x && rep_size.y < view_size.y) {
        for (int i = 0; i < rep_size.y; ++i)
            for (int j = 0; j < view_size.x; ++j) {
                int num = 0, den = 0;
                int ks = static_cast<int>(i * view_size.y / rep_size.y), ke = static_cast<int>((i + 1) * view_size.y / rep_size.y);
                int ls = static_cast<int>(j * (rep_size.x * 2) / view_size.x), le = static_cast<int>((j + 1) * (rep_size.x * 2) / view_size.x);
                for (int k = ks; k < ke; ++k) {
                    num += view_alpha_board[utility::get_index(view_size, k, j)];
                    ++den;
                }
                for (int l = ls; l < le; ++l)
                    alpha_board[utility::get_index(size, rep_pos + Vec2<int>{l, i})] = num / den;
            }
    }
    if ((rep_size.x * 2) >= view_size.x && rep_size.y >= view_size.y) {
        for (int i = 0; i < view_size.y; ++i)
            for (int j = 0; j < view_size.x; ++j) {
                int num = 0, den = 0;
                int ks = static_cast<int>(i * rep_size.y / view_size.y), ke = static_cast<int>((i + 1) * rep_size.y / view_size.y);
                int ls = static_cast<int>(j * (rep_size.x * 2) / view_size.x), le = static_cast<int>((j + 1) * (rep_size.x * 2) / view_size.x);
                num += view_alpha_board[view_size.x * i + j];
                ++den;
                for (int k = ks; k < ke; ++k)
                    for (int l = ls; l < le; ++l)
                        alpha_board[size.x * (rep_pos.y + k) + rep_pos.x + l] = num / den;
            }
    }
    if ((rep_size.x * 2) < view_size.x && rep_size.y >= view_size.y) {
        for (int i = 0; i < view_size.y; ++i)
            for (int j = 0; j < (rep_size.x * 2); ++j) {
                int num = 0, den = 0;
                int ks = static_cast<int>(i * rep_size.y / view_size.y), ke = static_cast<int>((i + 1) * rep_size.y / view_size.y);
                int ls = static_cast<int>(j * view_size.x / (rep_size.x * 2)), le = static_cast<int>((j + 1) * view_size.x / (rep_size.x * 2));
                for (int l = ls; l < le; ++l) {
                    num += view_alpha_board[utility::get_index(view_size, i, l)];
                    ++den;
                }
                for (int k = ks; k < ke; ++k)
                    alpha_board[utility::get_index(size, rep_pos + Vec2<int>{j, k})] = num / den;
            }
    }
}

void Console::set_char_board(const string& str, int y) {
    memcpy(char_board + utility::get_index(size, y, 0), str.c_str(), str.length() * sizeof(char));
}

void Console::apply_alpha_board_pause_effect() {
    const auto& pause = SpriteArchive::instance().get_sprite(SpriteIndex::pause);
    for (int i = 0; i < pause.size.y; ++i)
        for (int j = 0; j < pause.size.x; ++j) {
            alpha_board[size.x * i + j * 2] = min(alpha_board[size.x * i + j * 2] + pause.alpha[pause.size.x * i + j], 255);
            alpha_board[size.x * i + j * 2 + 1] = min(alpha_board[size.x * i + j * 2 + 1] + pause.alpha[pause.size.x * i + j], 255);
        }
}

void Console::apply_alpha_board_restart_room_effect(double ratio, bool fade_out) {
    if (!fade_out && ratio == 1.0 || fade_out && ratio == 0.0) return;
    ratio = - cos(ratio * numbers::pi) / 2 + 0.5;
    for (int i = 0; i < size.y; ++i)
        for (int j = 0; j < size.x; ++j)
            if (fade_out && j < ratio * size.x)
                alpha_board[size.x * i + j] = 0;
            else if (!fade_out && j > ratio * size.x)
                alpha_board[size.x * i + j] = 0;
}

void Console::set_char_board_from_alpha_board() {
    const char* const ascii = R"(@@@@@@@@@@@@@@@@@@@@@$$$$$$$$$$$$$$$$$$$$$$$$$########BBBB\\\\\\EEEEEEEE96Mg88GGGRRRR555%%%&&&DSSSbbd33PPeNNOaHHHssssqFF444CC22AAZmohKK===ww{{{{XXXXz[[ccVn]]LL???ffT7++++++JJJJJyyvvY))<>xxx______rrrrjjj//*~|^^^!!!!IIIIiii;;;""""::::--,,''''```.......      )";
    for (int i = 0; i < size.y; ++i)
        for (int j = 0; j < size.x; ++j)
            char_board[size.x * i + j] = ascii[255 - alpha_board[size.x * i + j]];
}

void Console::draw() {
    const char* const home = "\033[H";
    fwrite(home, sizeof(char), strlen(home), stdout);
    fwrite(char_board, sizeof(char), size.area(), stdout);
}