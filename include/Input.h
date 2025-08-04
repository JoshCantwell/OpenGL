#pragma once

#include <wtypesbase.h>
#include <Windows.h>
#include <unordered_map>

class Input {
	public:
		void update(HWND hwnd, bool paused);

		bool keyDown(int key) const;
		bool keyPressed(int key);
		int getMouseDeltaX() const { return deltaX; }
		int getMouseDeltaY() const { return deltaY; }

	private:
		std::unordered_map<int, bool> keyStates;
		int lastX = 0, lastY = 0;
		int deltaX = 0, deltaY = 0;

		bool cursorLocked = true;  // Cursor locked initially

		bool prevPKeyState = false; // To detect key press toggle 
};
