#include "inputgm.h"

namespace GM {

	bool* isKeyReleased = (bool*)(0xB64AA0);
	bool* isKeyPressed = (bool*)(0x0B64BA0);
	bool* isKeyDown = (bool*)(0xB64CD0);
	bool* isMouseButtonReleased = (bool*)(0xB65210);
	bool* isMouseButtonPressed = (bool*)(0xB65290);
	bool* isMouseButtonDown = (bool*)(0xB65250);
	int* mouseX = (int*)(0xB64A60);
	int* mouseY = (int*)(0xB64A30);
	HCURSOR* hCursor = (HCURSOR*)(0xB57D38);

}