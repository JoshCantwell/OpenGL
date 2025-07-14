#pragma once
#include <windows.h>

class Window {
	public:
		Window(HINSTANCE hInstance, int width, int height, const char* title);
		~Window();

		HWND getHWND() const { return hwnd; }
		HDC getHDC() const { return hdc; }
		bool processMessages();

	private:
		HWND hwnd;
		HDC hdc;
		HGLRC hglrc;
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

