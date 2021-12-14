#include "GuiButton.hpp"

using namespace std;

GuiButton::GuiButton(const Vec2<double>& pos, SpriteIndex sprite_index) : Object(pos) {
	sprite_info.sprite_index = sprite_index;
	original_pos = pos;
}

void GuiButton::step() {
	if (is_focus) {
		if (focus_effect_index < focus_effect_index_max) {
			++focus_effect_index;
			sprite_info.image_index = utility::lerp(0, SpriteArchive::instance().get_sprite(sprite_info.sprite_index).number - 1,
				1.0 * focus_effect_index / focus_effect_index_max);
		}
	}
	else {
		if (focus_effect_index > 0) {
			--focus_effect_index;
			sprite_info.image_index = utility::lerp(0, SpriteArchive::instance().get_sprite(sprite_info.sprite_index).number - 1,
				1.0 * focus_effect_index / focus_effect_index_max);
		}
	}
	if (is_trigger_start) {
		if (trigger_motion_index == trigger_motion_index_max) {
			is_trigger_end = true;
		}
		else {
			trigger_motion_index++;
			int m = trigger_motion_index_max * 2 / 3;
			int x = trigger_motion_index;
			int xmax = trigger_motion_index_max;
			int y = static_cast<int>(original_pos.y) - max<int>(-x * (x - m) * 9 / ((m * m) / 4),
				-(x - m) * (x - xmax) * 4 / ((xmax - m) * (xmax - m) / 4));
			pos.y = y;
		}
	}
	if (is_denied) {
		if (denied_motion_index == denied_motion_index_max) {
			is_denied = false;
			denied_motion_index = 0;
		}
		else {
			denied_motion_index++;
			int x = denied_motion_index;
			int xmax = denied_motion_index_max;
			int y = static_cast<int>(original_pos.x) + 
				static_cast<int>((cos(numbers::pi * x / xmax) + 1) / 2 * (sin(numbers::pi * 6 * x / xmax)) * 4);
			pos.x = y;
		}
	}
}

void GuiButton::trigger() {
	is_trigger_start = true;
}

void GuiButton::denied() {
	is_denied = true;
	denied_motion_index = 0;
}

void GuiButton::focus() {
	is_focus = true;
}

void GuiButton::unfocus() {
	is_focus = false;
}