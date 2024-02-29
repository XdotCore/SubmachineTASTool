#include "input.h"
#include <string>
#include <sstream>
#include <iostream>
#include <map>

std::map<MouseButton, std::string> MouseButtonNames = {
	{ MouseButton::mb_any, "mb_any" },
	{ MouseButton::mb_none, "mb_none" },
	{ MouseButton::mb_left, "mb_left" },
	{ MouseButton::mb_right, "mb_right" },
	{ MouseButton::mb_middle, "mb_middle" },
	{ MouseButton::mb_side1, "mb_side1" },
	{ MouseButton::mb_side2, "mb_side2" }
};

std::map<std::string, MouseButton> NameToMouseButton = {
	{ "mb_any", MouseButton::mb_any, },
	{ "mb_none", MouseButton::mb_none, },
	{ "mb_left", MouseButton::mb_left, },
	{ "mb_right", MouseButton::mb_right, },
	{ "mb_middle", MouseButton::mb_middle, },
	{ "mb_side1", MouseButton::mb_side1, },
	{ "mb_side2", MouseButton::mb_side2, }
};

std::map<VirtualKey, std::string> KeyNames = {
	{ VirtualKey::vk_nokey, "vk_nokey" },
	{ VirtualKey::vk_anykey, "vk_anykey" },
	{ VirtualKey::vk_backspace, "vk_backspace" },
	{ VirtualKey::vk_tab, "vk_tab" },
	{ VirtualKey::vk_enter, "vk_enter" },
	{ VirtualKey::vk_return, "vk_return" },
	{ VirtualKey::vk_shift, "vk_shift" },
	{ VirtualKey::vk_control, "vk_control" },
	{ VirtualKey::vk_alt, "vk_alt" },
	{ VirtualKey::vk_pause, "vk_pause" },
	{ VirtualKey::vk_escape, "vk_escape" },
	{ VirtualKey::vk_space, "vk_space" },
	{ VirtualKey::vk_pageup, "vk_pageup" },
	{ VirtualKey::vk_pagedown, "vk_pagedown" },
	{ VirtualKey::vk_end, "vk_end" },
	{ VirtualKey::vk_home, "vk_home" },
	{ VirtualKey::vk_left, "vk_left" },
	{ VirtualKey::vk_up, "vk_up" },
	{ VirtualKey::vk_right, "vk_right" },
	{ VirtualKey::vk_down, "vk_down" },
	{ VirtualKey::vk_printscreen, "vk_printscreen" },
	{ VirtualKey::vk_insert, "vk_insert" },
	{ VirtualKey::vk_delete, "vk_delete" },
	{ VirtualKey::vk_0, "vk_0" },
	{ VirtualKey::vk_1, "vk_1" },
	{ VirtualKey::vk_2, "vk_2" },
	{ VirtualKey::vk_3, "vk_3" },
	{ VirtualKey::vk_4, "vk_4" },
	{ VirtualKey::vk_5, "vk_5" },
	{ VirtualKey::vk_6, "vk_6" },
	{ VirtualKey::vk_7, "vk_7" },
	{ VirtualKey::vk_8, "vk_8" },
	{ VirtualKey::vk_9, "vk_9" },
	{ VirtualKey::vk_A, "vk_A" },
	{ VirtualKey::vk_B, "vk_B" },
	{ VirtualKey::vk_C, "vk_C" },
	{ VirtualKey::vk_D, "vk_D" },
	{ VirtualKey::vk_E, "vk_E" },
	{ VirtualKey::vk_F, "vk_F" },
	{ VirtualKey::vk_G, "vk_G" },
	{ VirtualKey::vk_H, "vk_H" },
	{ VirtualKey::vk_I, "vk_I" },
	{ VirtualKey::vk_J, "vk_J" },
	{ VirtualKey::vk_K, "vk_K" },
	{ VirtualKey::vk_L, "vk_L" },
	{ VirtualKey::vk_M, "vk_M" },
	{ VirtualKey::vk_N, "vk_N" },
	{ VirtualKey::vk_O, "vk_O" },
	{ VirtualKey::vk_P, "vk_P" },
	{ VirtualKey::vk_Q, "vk_Q" },
	{ VirtualKey::vk_R, "vk_R" },
	{ VirtualKey::vk_S, "vk_S" },
	{ VirtualKey::vk_T, "vk_T" },
	{ VirtualKey::vk_U, "vk_U" },
	{ VirtualKey::vk_V, "vk_V" },
	{ VirtualKey::vk_W, "vk_W" },
	{ VirtualKey::vk_X, "vk_X" },
	{ VirtualKey::vk_Y, "vk_Y" },
	{ VirtualKey::vk_Z, "vk_Z" },
	{ VirtualKey::vk_numpad0, "vk_numpad0" },
	{ VirtualKey::vk_numpad1, "vk_numpad1" },
	{ VirtualKey::vk_numpad2, "vk_numpad2" },
	{ VirtualKey::vk_numpad3, "vk_numpad3" },
	{ VirtualKey::vk_numpad4, "vk_numpad4" },
	{ VirtualKey::vk_numpad5, "vk_numpad5" },
	{ VirtualKey::vk_numpad6, "vk_numpad6" },
	{ VirtualKey::vk_numpad7, "vk_numpad7" },
	{ VirtualKey::vk_numpad8, "vk_numpad8" },
	{ VirtualKey::vk_numpad9, "vk_numpad9" },
	{ VirtualKey::vk_multiply, "vk_multiply" },
	{ VirtualKey::vk_add, "vk_add" },
	{ VirtualKey::vk_subtract, "vk_subtract" },
	{ VirtualKey::vk_decimal, "vk_decimal" },
	{ VirtualKey::vk_divide, "vk_divide" },
	{ VirtualKey::vk_f1, "vk_f1" },
	{ VirtualKey::vk_f2, "vk_f2" },
	{ VirtualKey::vk_f3, "vk_f3" },
	{ VirtualKey::vk_f4, "vk_f4" },
	{ VirtualKey::vk_f5, "vk_f5" },
	{ VirtualKey::vk_f6, "vk_f6" },
	{ VirtualKey::vk_f7, "vk_f7" },
	{ VirtualKey::vk_f8, "vk_f8" },
	{ VirtualKey::vk_f9, "vk_f9" },
	{ VirtualKey::vk_f10, "vk_f10" },
	{ VirtualKey::vk_f11, "vk_f11" },
	{ VirtualKey::vk_f12, "vk_f12" },
	{ VirtualKey::vk_lshift, "vk_lshift" },
	{ VirtualKey::vk_rshift, "vk_rshift" },
	{ VirtualKey::vk_lcontrol, "vk_lcontrol" },
	{ VirtualKey::vk_rcontrol, "vk_rcontrol" },
	{ VirtualKey::vk_lalt, "vk_lalt" },
	{ VirtualKey::vk_ralt, "vk_ralt" }
};

std::map<std::string, VirtualKey> NameToKey = {
	{ "vk_nokey", VirtualKey::vk_nokey, },
	{ "vk_anykey", VirtualKey::vk_anykey, },
	{ "vk_backspace", VirtualKey::vk_backspace, },
	{ "vk_tab", VirtualKey::vk_tab, },
	{ "vk_enter", VirtualKey::vk_enter, },
	{ "vk_return", VirtualKey::vk_return, },
	{ "vk_shift", VirtualKey::vk_shift, },
	{ "vk_control", VirtualKey::vk_control, },
	{ "vk_alt", VirtualKey::vk_alt, },
	{ "vk_pause", VirtualKey::vk_pause, },
	{ "vk_escape", VirtualKey::vk_escape, },
	{ "vk_space", VirtualKey::vk_space, },
	{ "vk_pageup", VirtualKey::vk_pageup, },
	{ "vk_pagedown", VirtualKey::vk_pagedown, },
	{ "vk_end", VirtualKey::vk_end, },
	{ "vk_home", VirtualKey::vk_home, },
	{ "vk_left", VirtualKey::vk_left, },
	{ "vk_up", VirtualKey::vk_up, },
	{ "vk_right", VirtualKey::vk_right, },
	{ "vk_down", VirtualKey::vk_down, },
	{ "vk_printscreen", VirtualKey::vk_printscreen, },
	{ "vk_insert", VirtualKey::vk_insert, },
	{ "vk_delete", VirtualKey::vk_delete, },
	{ "vk_0", VirtualKey::vk_0, },
	{ "vk_1", VirtualKey::vk_1, },
	{ "vk_2", VirtualKey::vk_2, },
	{ "vk_3", VirtualKey::vk_3, },
	{ "vk_4", VirtualKey::vk_4, },
	{ "vk_5", VirtualKey::vk_5, },
	{ "vk_6", VirtualKey::vk_6, },
	{ "vk_7", VirtualKey::vk_7, },
	{ "vk_8", VirtualKey::vk_8, },
	{ "vk_9", VirtualKey::vk_9, },
	{ "vk_A", VirtualKey::vk_A, },
	{ "vk_B", VirtualKey::vk_B, },
	{ "vk_C", VirtualKey::vk_C, },
	{ "vk_D", VirtualKey::vk_D, },
	{ "vk_E", VirtualKey::vk_E, },
	{ "vk_F", VirtualKey::vk_F, },
	{ "vk_G", VirtualKey::vk_G, },
	{ "vk_H", VirtualKey::vk_H, },
	{ "vk_I", VirtualKey::vk_I, },
	{ "vk_J", VirtualKey::vk_J, },
	{ "vk_K", VirtualKey::vk_K, },
	{ "vk_L", VirtualKey::vk_L, },
	{ "vk_M", VirtualKey::vk_M, },
	{ "vk_N", VirtualKey::vk_N, },
	{ "vk_O", VirtualKey::vk_O, },
	{ "vk_P", VirtualKey::vk_P, },
	{ "vk_Q", VirtualKey::vk_Q, },
	{ "vk_R", VirtualKey::vk_R, },
	{ "vk_S", VirtualKey::vk_S, },
	{ "vk_T", VirtualKey::vk_T, },
	{ "vk_U", VirtualKey::vk_U, },
	{ "vk_V", VirtualKey::vk_V, },
	{ "vk_W", VirtualKey::vk_W, },
	{ "vk_X", VirtualKey::vk_X, },
	{ "vk_Y", VirtualKey::vk_Y, },
	{ "vk_Z", VirtualKey::vk_Z, },
	{ "vk_numpad0", VirtualKey::vk_numpad0, },
	{ "vk_numpad1", VirtualKey::vk_numpad1, },
	{ "vk_numpad2", VirtualKey::vk_numpad2, },
	{ "vk_numpad3", VirtualKey::vk_numpad3, },
	{ "vk_numpad4", VirtualKey::vk_numpad4, },
	{ "vk_numpad5", VirtualKey::vk_numpad5, },
	{ "vk_numpad6", VirtualKey::vk_numpad6, },
	{ "vk_numpad7", VirtualKey::vk_numpad7, },
	{ "vk_numpad8", VirtualKey::vk_numpad8, },
	{ "vk_numpad9", VirtualKey::vk_numpad9, },
	{ "vk_multiply", VirtualKey::vk_multiply, },
	{ "vk_add", VirtualKey::vk_add, },
	{ "vk_subtract", VirtualKey::vk_subtract, },
	{ "vk_decimal", VirtualKey::vk_decimal, },
	{ "vk_divide", VirtualKey::vk_divide, },
	{ "vk_f1", VirtualKey::vk_f1, },
	{ "vk_f2", VirtualKey::vk_f2, },
	{ "vk_f3", VirtualKey::vk_f3, },
	{ "vk_f4", VirtualKey::vk_f4, },
	{ "vk_f5", VirtualKey::vk_f5, },
	{ "vk_f6", VirtualKey::vk_f6, },
	{ "vk_f7", VirtualKey::vk_f7, },
	{ "vk_f8", VirtualKey::vk_f8, },
	{ "vk_f9", VirtualKey::vk_f9, },
	{ "vk_f10", VirtualKey::vk_f10, },
	{ "vk_f11", VirtualKey::vk_f11, },
	{ "vk_f12", VirtualKey::vk_f12, },
	{ "vk_lshift", VirtualKey::vk_lshift, },
	{ "vk_rshift", VirtualKey::vk_rshift, },
	{ "vk_lcontrol", VirtualKey::vk_lcontrol, },
	{ "vk_rcontrol", VirtualKey::vk_rcontrol, },
	{ "vk_lalt", VirtualKey::vk_lalt, },
	{ "vk_ralt", VirtualKey::vk_ralt, }
};

std::string GetMouseButtonName(MouseButton mb) {
	return MouseButtonNames[mb];
}

MouseButton GetMouseButtonFromName(std::string name) {
	return NameToMouseButton[name];
}

std::string GetKeyName(VirtualKey key) {
	return KeyNames[key];
}

VirtualKey GetKeyFromName(std::string name) {
	return NameToKey[name];
}

bool* isKeyReleased = (bool*)(0xB64AA0);
bool* isKeyPressed = (bool*)(0x0B64BA0);
bool* isKeyDown = (bool*)(0xB64CD0);
bool* isMouseButtonReleased = (bool*)(0xB65210);
bool* isMouseButtonPressed = (bool*)(0xB65290);
bool* isMouseButtonDown = (bool*)(0xB65250);
int* mouse_x = (int*)(0xB64A60);
int* mouse_y = (int*)(0xB64A30);
HCURSOR* hCursor = (HCURSOR*)(0xB57D38);

std::string FrameInput::Serialize() const {
	std::stringstream text;

	for (const auto& [mb, name] : MouseButtonNames) {
		bool isReleased = isMouseButtonReleased[mb];
		bool isPressed = isMouseButtonPressed[mb];
		bool isDown = isMouseButtonDown[mb];

		// compression (:
		if (!isReleased && !isPressed && !isDown)
			continue;

		text << "mouseButton" << '\n';
		text << "name " << name << '\n';
		text << "isReleased " << isReleased << '\n';
		text << "isPressed " << isPressed << '\n';
		text << "isDown " << isDown << '\n';
		text << "end" << '\n';
	}
	for (const auto& [key, name] : KeyNames) {
		bool isReleased = isKeyReleased[key];
		bool isPressed = isKeyPressed[key];
		bool isDown = isKeyDown[key];

		// compression (:
		if (!isReleased && !isPressed && !isDown)
			continue;

		text << "virtualKey" << '\n';
		text << "name " << name << '\n';
		text << "isReleased " << isReleased << '\n';
		text << "isPressed " << isPressed << '\n';
		text << "isDown " << isDown << '\n';
		text << "end" << '\n';
	}
	text << "mouse" << '\n';
	text << "x " << mouse_x << '\n';
	text << "y " << mouse_y << '\n';
	text << "end" << '\n';

	return text.str();
}

void FrameInput::Unserialize(std::ifstream& loadFile) {
	std::string line;

	while (std::getline(loadFile, line, '\n')) {
		if (line == "end")
			break;

		if (line == "mouseButton") {
			bool gotMouseButton = false;

			MouseButton mb;
			bool isReleased = false;
			bool isPressed = false;
			bool isDown = false;

			while (std::getline(loadFile, line, '\n')) {
				if (line == "end")
					break;
				
				if (line.starts_with("name ")) {
					mb = GetMouseButtonFromName(line.substr(5));
					gotMouseButton = true;
				}
				else if (line.starts_with("isReleased "))
					isReleased = line[11] == '1';
				else if (line.starts_with("isPressed "))
					isPressed = line[10] == '1';
				else if (line.starts_with("isDown "))
					isDown = line[7] = '1';
			}

			if (!gotMouseButton)
				continue;

			isMouseButtonReleased[mb] = isReleased;
			isMouseButtonPressed[mb] = isPressed;
			isMouseButtonDown[mb] = isDown;
		}
		else if (line == "virtualKey") {
			bool gotKey = false;

			VirtualKey key;
			bool isReleased = false;
			bool isPressed = false;
			bool isDown = false;

			while (std::getline(loadFile, line, '\n')) {
				if (line == "end")
					break;

				if (line.starts_with("name ")) {
					key = GetKeyFromName(line.substr(5));
					gotKey = true;
				}
				else if (line.starts_with("isReleased "))
					isReleased = line[11] == '1';
				else if (line.starts_with("isPressed "))
					isPressed = line[10] == '1';
				else if (line.starts_with("isDown "))
					isDown = line[7] = '1';
			}

			if (!gotKey)
				continue;

			isKeyReleased[key] = isReleased;
			isKeyPressed[key] = isPressed;
			isKeyDown[key] = isDown;
		}
		else if (line == "mouse") {
			while (std::getline(loadFile, line, '\n')) {
				if (line == "end")
					break;

				if (line.starts_with("x "))
					mouse_x = std::stoi(line.substr(2));
				else if (line.starts_with("y "))
					mouse_y = std::stoi(line.substr(2));
			}
		}
	}
}