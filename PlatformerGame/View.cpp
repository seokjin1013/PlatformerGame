#include "View.hpp"

using namespace std;

View::View() {
    alpha_board = new int[MAX_RESOLUTION.area() * 2];
    alpha_board_init = new int[(MAX_RESOLUTION + MAX_RESOLUTION_BOARDER * 2 * 2).area() * 2];
    filter_board = new Vec2<double>[MAX_RESOLUTION.area() * 2];
    clear();
}

View::~View() {
    delete[] alpha_board;
    delete[] alpha_board_init;
    delete[] filter_board;
}

void View::clear() {
    memset(alpha_board, 0, MAX_RESOLUTION.area() * 2 * sizeof(int));
    memset(alpha_board_init, 0, (MAX_RESOLUTION + MAX_RESOLUTION_BOARDER * 2 * 2).area() * 2 * sizeof(int));
    fill_n(filter_board, MAX_RESOLUTION.area() * 2, Vec2<double>{ 0, 0 });
}

void View::draw(const Room& room) {
    const auto& pool = room.get_pool();
    const auto& view = room.view_info;
    size = view.size;
    size.x *= 2;
    auto border_size = MAX_RESOLUTION_BOARDER;
    border_size.x *= 2;
    for (const auto* e : pool) {
        const auto& pos = e->get_pos();
        const auto& sprite_info = e->get_sprite_info();
        draw_sprite(alpha_board_init, size + border_size * 2, sprite_info, pos - view.pos + view.size / 2 + MAX_RESOLUTION_BOARDER);
    }
    apply_filter_time_recall_effect(view.time_recall_effect_strength, view.time_recall_effect_period);
    draw_set_filter(alpha_board, alpha_board_init, border_size, filter_board);
    draw_time_recall_bar(alpha_board, view);
}

void View::draw_sprite(int* board, const Vec2<int>& size, const SpriteInfo& sprite_info, const Vec2<double>& pos) {
    const Sprite& sprite = SpriteArchive::instance().get_sprite(sprite_info.sprite_index);
    Vec2<double> nearest = { round((pos.x - 0.5) * 2) / 2, round(pos.y - 0.5) };
    for (int i = 0; i < sprite.size.y; ++i)
        for (int j = 0; j < sprite.size.x; ++j) {
            int sprite_alpha_index = utility::get_index(sprite.size, sprite_info.image_index, i, j);
            if (sprite.alpha[sprite_alpha_index] > 0) {
                double y = nearest.y - sprite.center.y + i;
                double x = nearest.x - sprite.center.x + (sprite_info.image_scale.x == -1 ? sprite.size.x - j - 1 : j);
                int cell_y = static_cast<int>(y);
                int cell_x_left = static_cast<int>(x * 2);
                int cell_x_right = static_cast<int>(x * 2 + 1);
                if (!(cell_y >= 0 && cell_y < size.y)) continue;
                if (cell_x_left >= 0 && cell_x_left < size.x) {
                    int left_pixel_index = utility::get_index(size, cell_y, cell_x_left);
                    board[left_pixel_index] += sprite.alpha[sprite_alpha_index];
                    board[left_pixel_index] = min(board[left_pixel_index], 255);
                }
                if (cell_x_right >= 0 && cell_x_right < size.x) {
                    int right_pixel_index = utility::get_index(size, cell_y, cell_x_right);
                    board[right_pixel_index] += sprite.alpha[sprite_alpha_index];
                    board[right_pixel_index] = min(board[right_pixel_index], 255);
                }
            }
        }
}

void View::draw_set_filter(int* dst, int* src, const Vec2<int>& border, Vec2<double>* filter_board) {
    int y, x;
    for (int i = 0; i < size.y; ++i)
        for (int j = 0; j < size.x; ++j) {
            y = i + border.y + static_cast<int>(filter_board[size.x * i + j].y);
            x = j + border.x + static_cast<int>(filter_board[size.x * i + j].x);
            dst[size.x * i + j] = src[(size.x + border.x * 2) * y + x];
        }
}

void View::draw_time_recall_bar(int* board, const ViewInfo& view) {
    if (view.time_recall_gauge_show >= 1) {
        int border = size.y / 5;
        int thinness = view.time_recall_gauge_show == 2 ? 8 : 4;
        for (int i = border * 2; i <= size.x - border * 2; ++i) {
            board[utility::get_index(size, size.y - border - thinness / 2, i)] = 255;
            board[utility::get_index(size, size.y - border - thinness / 2 + thinness - 1, i)] = 255;
        }
        for (int i = size.y - border - thinness / 2; i <= size.y - border - thinness / 2 + thinness - 1; ++i) {
            board[utility::get_index(size, i, border * 2)] = 255;
            board[utility::get_index(size, i, size.x - border * 2)] = 255;
            board[utility::get_index(size, i, border * 2 + 1)] = 255;
            board[utility::get_index(size, i, size.x - border * 2 - 1)] = 255;
        }
        for (int i = border * 2 + 2; i <= utility::lerp<int>(border * 2 + 2, size.x - border * 2 - 2, view.time_recall_gauge_rate); ++i)
            for (int j = size.y - border - thinness / 2; j <= size.y - border - thinness / 2 + thinness - 1; ++j)
                board[utility::get_index(size, j, i)] = min(255, board[utility::get_index(size, j, i)] + 180);
    }
}

void View::apply_filter_time_recall_effect(double strength, double period) {
    for (int i = 0; i < size.y; ++i)
        for (int j = 0; j < size.x; ++j)
            filter_board[size.x * i + j].x = cos(numbers::pi * 2 * (i / 50.0 + period)) * strength;
}

const int* View::get_alpha_board() const {
    return alpha_board;
}

const Vec2<int>& View::get_size() const {
    return size;
}