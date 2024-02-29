#pragma once

#include <windows.h>
#include <string>
#include <fstream>

enum MouseButton : int {
	mb_any = -1,
	mb_none = 0,
	mb_left = 1,
	mb_right = 2,
	mb_middle = 3,
	mb_side1 = 4,
	mb_side2 = 5
};

std::string GetMouseButtonName(MouseButton mb);
MouseButton GetMouseButtonFromName(std::string name);

enum VirtualKey : int {
	vk_nokey = 0,
	vk_anykey = 1,
	vk_backspace = 8,
	vk_tab = 9,
	vk_enter = 13,
	vk_return = 13,
	vk_shift = 16,
	vk_control = 17,
	vk_alt = 18,
	vk_pause = 19,
	vk_escape = 27,
	vk_space = 32,
	vk_pageup = 33,
	vk_pagedown = 34,
	vk_end = 35,
	vk_home = 36,
	vk_left = 37,
	vk_up = 38,
	vk_right = 39,
	vk_down = 40,
	vk_printscreen = 44,
	vk_insert = 45,
	vk_delete = 46,
	vk_0 = '0',
	vk_1 = '1',
	vk_2 = '2',
	vk_3 = '3',
	vk_4 = '4',
	vk_5 = '5',
	vk_6 = '6',
	vk_7 = '7',
	vk_8 = '8',
	vk_9 = '9',
	vk_A = 'A',
	vk_B = 'B',
	vk_C = 'C',
	vk_D = 'D',
	vk_E = 'E',
	vk_F = 'F',
	vk_G = 'G',
	vk_H = 'H',
	vk_I = 'I',
	vk_J = 'J',
	vk_K = 'K',
	vk_L = 'L',
	vk_M = 'M',
	vk_N = 'N',
	vk_O = 'O',
	vk_P = 'P',
	vk_Q = 'Q',
	vk_R = 'R',
	vk_S = 'S',
	vk_T = 'T',
	vk_U = 'U',
	vk_V = 'V',
	vk_W = 'W',
	vk_X = 'X',
	vk_Y = 'Y',
	vk_Z = 'Z',
	vk_numpad0 = 96,
	vk_numpad1 = 97,
	vk_numpad2 = 98,
	vk_numpad3 = 99,
	vk_numpad4 = 100,
	vk_numpad5 = 101,
	vk_numpad6 = 102,
	vk_numpad7 = 103,
	vk_numpad8 = 104,
	vk_numpad9 = 105,
	vk_multiply = 106,
	vk_add = 107,
	vk_subtract = 109,
	vk_decimal = 110,
	vk_divide = 111,
	vk_f1 = 112,
	vk_f2 = 113,
	vk_f3 = 114,
	vk_f4 = 115,
	vk_f5 = 116,
	vk_f6 = 117,
	vk_f7 = 118,
	vk_f8 = 119,
	vk_f9 = 120,
	vk_f10 = 121,
	vk_f11 = 122,
	vk_f12 = 123,
	vk_lshift = 160,
	vk_rshift = 161,
	vk_lcontrol = 162,
	vk_rcontrol = 163,
	vk_lalt = 164,
	vk_ralt = 165
};

std::string GetKeyName(VirtualKey key);
VirtualKey GetKeyFromName(std::string name);

extern bool* isKeyReleased;
extern bool* isKeyPressed;
extern bool* isKeyDown;
extern bool* isMouseButtonReleased;
extern bool* isMouseButtonPressed;
extern bool* isMouseButtonDown;
extern int* mouse_x;
extern int* mouse_y;
extern HCURSOR* hCursor;

struct FrameInput {
	bool isKeyReleased[256] = {};
	bool isKeyPressed[256] = {};
	bool isKeyDown[256] = {};
	bool isMouseButtonReleased[5] = {};
	bool isMouseButtonPressed[5] = {};
	bool isMouseButtonDown[5] = {};
	int mouse_x = 0;
	int mouse_y = 0;

	std::string Serialize() const;
	void Unserialize(std::ifstream& loadFile);
};
