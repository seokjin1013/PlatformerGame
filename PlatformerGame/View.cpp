#include "View.hpp"

using namespace std;

View::View() {
    alpha_board = new int[MAX_RESOLUTION.area() * 2];
    clear();
}

View::~View() {
    delete[] alpha_board;
}

void View::clear() {
    memset(alpha_board, 0, MAX_RESOLUTION.area() * sizeof(int));
}

void View::draw(const Room& room) {
    const auto& pool = room.get_pool();
    const auto& view = room.view_info;
    size = view.size;
    size.x *= 2;
    for (const auto* e : pool) {
        const auto& pos = e->get_pos();
        const auto& sprite_info = e->get_sprite_info();
        clear_rendering2(sprite_info, pos - view.pos + view.size / 2);
    }
    if (view.time_recall_gauge_show >= 1) {
        int border = size.y / 5;
        int thinness = view.time_recall_gauge_show == 2 ? 8 : 3;
        for (int i = border * 2; i <= size.x - border * 2; ++i) {
            alpha_board[utility::get_index(size, size.y - border - thinness / 2, i)] = 255;
            alpha_board[utility::get_index(size, size.y - border - thinness / 2 + thinness - 1, i)] = 255;
        }
        for (int i = size.y - border - thinness / 2; i <= size.y - border - thinness / 2 + thinness - 1; ++i) {
            alpha_board[utility::get_index(size, i, border * 2)] = 255;
            alpha_board[utility::get_index(size, i, size.x - border * 2)] = 255;
            alpha_board[utility::get_index(size, i, border * 2 + 1)] = 255;
            alpha_board[utility::get_index(size, i, size.x - border * 2 - 1)] = 255;
        }
        for (int i = border * 2 + 2; i <= utility::lerp<int>(border * 2 + 2, size.x - border * 2 - 2, view.time_recall_gauge_rate); ++i)
            for (int j = size.y - border - thinness / 2; j <= size.y - border - thinness / 2 + thinness - 1; ++j)
                alpha_board[utility::get_index(size, j, i)] = min(255, alpha_board[utility::get_index(size, j, i)] + 180);
    }
}

void View::smooth_rendering(const SpriteInfo& sprite_info, const Vec2<double>& pos) {
    const Sprite& sprite = SpriteArchive::instance().get_sprite(sprite_info.sprite_index);
    Vec2<double> nearest = {round(pos.x), round(pos.y)};
    Vec2<double> dpos[4] = {{0, 0}, {-1, 0}, {-1, -1}, {0, -1}};
    for (int d = 0; d < 4; ++d) {
        double alpha = abs((pos + 0.5 - nearest + dpos[d]).area());
        for (int i = 0; i < sprite.size.y; ++i)
            for (int j = 0; j < sprite.size.x; ++j) {
                int sprite_alpha_index = utility::get_index(sprite.size, sprite_info.image_index, i, j);
                if (sprite.alpha[sprite_alpha_index] > 0) {
                    int y = static_cast<int>(nearest.y + dpos[d].y - sprite.center.y + i);
                    int x = static_cast<int>(nearest.x + dpos[d].x - sprite.center.x + (sprite_info.image_scale.x == -1 ? sprite.size.x - j - 1 : j));
                    x *= 2;
                    if (!(y >= 0 && y < size.y)) continue;
                    if (!(x >= 0 && x < size.x)) continue;
                    int left_pixel_index = utility::get_index(size, y, x);
                    alpha_board[left_pixel_index] += static_cast<int>(sprite.alpha[sprite_alpha_index] * alpha);
                    alpha_board[left_pixel_index + 1] += static_cast<int>(sprite.alpha[sprite_alpha_index] * alpha);
                    alpha_board[left_pixel_index] = min(alpha_board[left_pixel_index], 255);
                    alpha_board[left_pixel_index + 1] = min(alpha_board[left_pixel_index + 1], 255);
                }
            }
    }
}

void View::clear_rendering(const SpriteInfo& sprite_info, const Vec2<double>& pos) {
    const Sprite& sprite = SpriteArchive::instance().get_sprite(sprite_info.sprite_index);
    Vec2<double> nearest = {round(pos.x - 0.5), round(pos.y - 0.5)};
    for (int i = 0; i < sprite.size.y; ++i)
        for (int j = 0; j < sprite.size.x; ++j) {
            int sprite_alpha_index = utility::get_index(sprite.size, sprite_info.image_index, i, j);
            if (sprite.alpha[sprite_alpha_index] > 0) {
                int y = static_cast<int>(nearest.y - sprite.center.y + i);
                int x = static_cast<int>(nearest.x - sprite.center.x + (sprite_info.image_scale.x == -1 ? sprite.size.x - j - 1 : j));
                x *= 2;
                if (!(y >= 0 && y < size.y)) continue;
                if (!(x >= 0 && x < size.x)) continue;
                int left_pixel_index = utility::get_index(size, y, x);
                alpha_board[left_pixel_index] += sprite.alpha[sprite_alpha_index];
                alpha_board[left_pixel_index + 1] += sprite.alpha[sprite_alpha_index];
                alpha_board[left_pixel_index] = min(alpha_board[left_pixel_index], 255);
                alpha_board[left_pixel_index + 1] = min(alpha_board[left_pixel_index + 1], 255);
            }
        }
}

void View::clear_rendering2(const SpriteInfo& sprite_info, const Vec2<double>& pos) {
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
                    alpha_board[left_pixel_index] += sprite.alpha[sprite_alpha_index];
                    alpha_board[left_pixel_index] = min(alpha_board[left_pixel_index], 255);
                }
                if (cell_x_right >= 0 && cell_x_right < size.x) {
                    int right_pixel_index = utility::get_index(size, cell_y, cell_x_right);
                    alpha_board[right_pixel_index] += sprite.alpha[sprite_alpha_index];
                    alpha_board[right_pixel_index] = min(alpha_board[right_pixel_index], 255);
                }
            }
        }
}

const int* View::get_alpha_board() const {
    return alpha_board;
}

const Vec2<int>& View::get_size() const {
    return size;
}