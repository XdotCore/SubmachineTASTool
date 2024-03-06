#pragma once

#include <string>
#include <fstream>
#include "GameMaker/inputgm.h"

std::string GetMouseButtonName(GM::MouseButton mb);
GM::MouseButton GetMouseButtonFromName(std::string name);

std::string GetKeyName(GM::VirtualKey key);
GM::VirtualKey GetKeyFromName(std::string name);

struct FrameInput {
	bool isKeyReleased[256] = {};
	bool isKeyPressed[256] = {};
	bool isKeyDown[256] = {};
	bool isMouseButtonReleased[5] = {};
	bool isMouseButtonPressed[5] = {};
	bool isMouseButtonDown[5] = {};
	int mouseX = 0;
	int mouseY = 0;

	std::string Serialize() const;
	void Unserialize(std::ifstream& loadFile);
};
