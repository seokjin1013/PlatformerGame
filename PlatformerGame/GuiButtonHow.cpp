#include "GuiButtonHow.hpp"

using namespace std;

GuiButtonHow::GuiButtonHow(const Vec2<double>& pos) : GuiButton(pos) {
	sprite_info.sprite_index = SpriteIndex::gui_button_how;
}

void GuiButtonHow::step() {

}

void GuiButtonHow::trigger() {
	is_trigger = true;
}

void GuiButtonHow::focus() {
	is_focus = true;
}

void GuiButtonHow::unfocus() {
	is_focus = false;

}