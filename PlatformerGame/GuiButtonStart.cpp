#include "GuiButtonStart.hpp"

using namespace std;

GuiButtonStart::GuiButtonStart(const Vec2<double>& pos) : GuiButton(pos) {
	sprite_info.sprite_index = SpriteIndex::gui_button_start;
}

void GuiButtonStart::step() {

}

void GuiButtonStart::trigger() {
	is_trigger = true;
}

void GuiButtonStart::focus() {
	is_focus = true;
}

void GuiButtonStart::unfocus() {
	is_focus = false;

}