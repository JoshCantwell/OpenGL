#include "../include/Input.h"
#include <Windows.h>

void Input::update() {
	for (int i = 0; i < 256; ++i)
		keyStates[i] = GetAsyncKeyState(i);
}

bool Input::keyDown(int vkCode) const {
	return (keyStates[vkCode] & 0x8000) != 0;
}

