#include "View.hpp"

using namespace std;

View::View() {
    alpha_board = new int[MAX_RESOLUTION.area() * 2];
    alpha_board_init = new int[(MAX_RESOLUTION + MAX_RESOLUTION_BOARDER * 2 * 2).area() * 2];
    filter_board_x = new double[MAX_RESOLUTION.area() * 2];
    filter_board_y = new double[MAX_RESOLUTION.area() * 2];
    clear();
}

View::~View() {
    delete[] alpha_board;
    delete[] alpha_board_init;
    delete[] filter_board_x;
    delete[] filter_board_y;
}

void View::clear() {
    memset(alpha_board, 0, MAX_RESOLUTION.area() * 2 * sizeof(int));
    memset(alpha_board_init, 0, (MAX_RESOLUTION + MAX_RESOLUTION_BOARDER * 2 * 2).area() * 2 * sizeof(int));
    memset(filter_board_x, 0, MAX_RESOLUTION.area() * 2 * sizeof(double));
    memset(filter_board_y, 0, MAX_RESOLUTION.area() * 2 * sizeof(double));
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
    auto focus = view.time_recall_effect_focus - view.pos + view.size / 2;
    apply_filter_time_recall_effect(view.time_recall_effect_strength, view.time_recall_effect_period, focus.x * 2, focus.y);
    draw_set_filter(alpha_board, alpha_board_init, border_size, filter_board_x, filter_board_y);
    draw_time_recall_bar(alpha_board, view);
    apply_information_effect(view.information_sprite, view.information_alpha);
}

void View::draw_sprite(int* board, const Vec2<int>& size, const SpriteInfo& sprite_info, const Vec2<double>& pos) {
    const Sprite& sprite = SpriteArchive::instance().get_sprite(sprite_info.sprite_index);
    Vec2<double> nearest = { round((pos.x - 0.5) * 2) / 2, round(pos.y - 0.5) };
    for (int i = 0; i < sprite.size.y; ++i)
        for (int j = 0; j < sprite.size.x; ++j) {
            int sprite_alpha_index = utility::get_index(sprite.size, sprite_info.image_index, i, j);
            if (sprite.alpha[sprite_alpha_index] > 0) {
                double y, x;
                if (sprite_info.image_angle == 0) {
                    y = nearest.y - sprite.center.y + (sprite_info.image_flip_y ? sprite.size.y - i - 1 : i);
                    x = nearest.x - sprite.center.x + (sprite_info.image_flip_x ? sprite.size.x - j - 1 : j);
                }
                else if (sprite_info.image_angle == 1) {
                    y = nearest.y - sprite.center.x + (sprite_info.image_flip_x ? sprite.size.x - j - 1 : j);
                    x = nearest.x + sprite.center.y - (sprite_info.image_flip_y ? sprite.size.y - i - 1 : i) - (sprite.center.y % 2 == 0);
                }
                else if (sprite_info.image_angle == 2) {
                    y = nearest.y + sprite.center.y - (sprite_info.image_flip_y ? sprite.size.y - i - 1 : i) - (sprite.center.y % 2 == 0);
                    x = nearest.x + sprite.center.x - (sprite_info.image_flip_x ? sprite.size.x - j - 1 : j) - (sprite.center.x % 2 == 0);
                }
                else if (sprite_info.image_angle == 3) {
                    y = nearest.y + sprite.center.x - (sprite_info.image_flip_x ? sprite.size.x - j - 1 : j) - (sprite.center.x % 2 == 0);
                    x = nearest.x - sprite.center.y + (sprite_info.image_flip_y ? sprite.size.y - i - 1 : i);
                }
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
    if (sprite_info.primary) {
        Vec2<double> nearest = { round((pos.x - 0.5) * 2) / 2, round(pos.y - 0.5) };
        for (int i = sprite_info.y1; i <= sprite_info.y2; ++i)
            for (int j = sprite_info.x1; j <= sprite_info.x2; ++j) {
                double y, x;
                y = nearest.y + i;
                x = nearest.x + j;
                int cell_y = static_cast<int>(y);
                int cell_x_left = static_cast<int>(x * 2);
                int cell_x_right = static_cast<int>(x * 2 + 1);
                if (!(cell_y >= 0 && cell_y < size.y)) continue;
                if (cell_x_left >= 0 && cell_x_left < size.x) {
                    int left_pixel_index = utility::get_index(size, cell_y, cell_x_left);
                    board[left_pixel_index] = 255;
                }
                if (cell_x_right >= 0 && cell_x_right < size.x) {
                    int right_pixel_index = utility::get_index(size, cell_y, cell_x_right);
                    board[right_pixel_index] = 255;
                }
            }
    }
}

void View::draw_set_filter(int* dst, int* src, const Vec2<int>& border, double* filter_board_x, double* filter_board_y) {
    int y, x;
    for (int i = 0; i < size.y; ++i)
        for (int j = 0; j < size.x; ++j) {
            y = i + border.y + static_cast<int>(filter_board_y[size.x * i + j]);
            x = j + border.x + static_cast<int>(filter_board_x[size.x * i + j]);
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
        int bar_fill_left = border * 2 + 2;
        int bar_fill_right = utility::lerp<int>(border * 2 + 2, size.x - border * 2 - 2, view.time_recall_gauge_rate);
        for (int i = bar_fill_left; i <= bar_fill_right; ++i)
            for (int j = size.y - border - thinness / 2; j <= size.y - border - thinness / 2 + thinness - 1; ++j)
                board[utility::get_index(size, j, i)] = min(255, board[utility::get_index(size, j, i)] + (i - bar_fill_left) * 255 / (bar_fill_right + 1 - bar_fill_left));
    }
}

void View::apply_filter_time_recall_effect(double strength, double period, double focus_x, double focus_y) {
    //double max_dist = hypot(max(abs(focus.y - 0), abs(focus.y - size.y)), max(abs(focus.x - 0), abs(focus.x - size.x)));
    double max_dist = max(abs(focus_y - 0), abs(focus_y - size.y)) + max(abs(focus_x - 0), abs(focus_x - size.x));
    double dist;
    double c, s;
    for (int i = 0; i < size.y; ++i)
        for (int j = 0; j < size.x; ++j) {
            dist = ((focus_y - i) > 0 ? focus_y - i : i - focus_y) + ((focus_x - j) > 0 ? focus_x - j : j - focus_x);
            c = cos(numbers::pi * 2 * (i / 20.0 + period));
            s = sin(numbers::pi * 2 * (j / 20.0 / 2 + period));
            filter_board_x[size.x * i + j] = c * strength * (1 + (dist / max_dist) * 3);
            filter_board_y[size.x * i + j] = s * strength / 2 * (1 + (dist / max_dist) * 3);
        }
}

void View::apply_information_effect(SpriteInfo information_info, double information_alpha) {
    if (information_alpha == 0.0) return;
    double x, y;
    for (int i = size.y * 6 / 10; i < size.y * 7 / 10; ++i) {
        x = (i - size.y * 6.0 / 10) / (size.y * 7.0 / 10 - size.y * 6.0 / 10);
        y = (cos(x * numbers::pi) + 1) / 2;
        for (int j = 0; j < size.x; ++j)
            alpha_board[size.x * i + j] = static_cast<int>(alpha_board[size.x * i + j] * (1 - information_alpha * (1 - y)));
    }
    for (int i = size.y * 7 / 10; i < size.y; ++i) {
        for (int j = 0; j < size.x; ++j)
            alpha_board[size.x * i + j] = static_cast<int>(alpha_board[size.x * i + j] * (1 - information_alpha));
    }
    if (information_alpha > 0.5)
        draw_sprite(alpha_board, size, information_info, { size.x / 4.0, size.y * 8.5 / 10 + 1 });
}

const int* View::get_alpha_board() const {
    return alpha_board;
}

const Vec2<int>& View::get_size() const {
    return size;
}