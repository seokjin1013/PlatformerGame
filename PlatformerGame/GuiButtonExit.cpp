#include "GuiButtonExit.hpp"

using namespace std;

GuiButtonExit::GuiButtonExit(const Vec2<double>& pos) : GuiButton(pos) {
	sprite_info.sprite_index = SpriteIndex::gui_button_exit;
}

void GuiButtonExit::step() {

}

void GuiButtonExit::trigger() {
	is_trigger = true;
}

void GuiButtonExit::focus() {
	is_focus = true;
}

void GuiButtonExit::unfocus() {
	is_focus = false;

}