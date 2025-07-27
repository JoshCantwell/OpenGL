#include "../include/Input.h"
#include <Windows.h>

void Input::update(HWND hwnd) {
    // Track key states
    for (int key = 0; key < 256; ++key) {
        keyStates[key] = (GetAsyncKeyState(key) & 0x8000) != 0;
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

    // Optional: re-center mouse
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
