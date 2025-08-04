#include <Input.h>
#include <Windows.h>


void Input::update(HWND hwnd, bool paused) {
	// Track key states
	for (int key = 0; key < 256; ++key) {
		keyStates[key] = (GetAsyncKeyState(key) & 0x8000) != 0;
	}

	if (paused) {
		// Don't track mouse movement or recenter the mouse
		deltaX = 0;
		deltaY = 0;
		return;
	}

	// Track mouse movement
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hwnd, &pt);

	static bool firstFrame = true;
	if (firstFrame) {
		lastX = pt.x;
		lastY = pt.y;
		firstFrame = false;
	}

	deltaX = pt.x - lastX;
	deltaY = pt.y - lastY;

	lastX = pt.x;
	lastY = pt.y;

	// Re-center mouse
	RECT rect;
	GetClientRect(hwnd, &rect);
	POINT center = { (rect.right - rect.left) / 2, (rect.bottom - rect.top) / 2 };
	ClientToScreen(hwnd, &center);
	SetCursorPos(center.x, center.y);

	lastX = (rect.right - rect.left) / 2;
	lastY = (rect.bottom - rect.top) / 2;
}
bool Input::keyDown(int key) const {
	auto it = keyStates.find(key);
	return it != keyStates.end() && it->second;
}

bool Input::keyPressed(int key) {
	static std::unordered_map<int, bool> previousStates;

	bool current = keyDown(key);
	bool previous = previousStates[key];
	previousStates[key] = current;

	return current && !previous;
}

