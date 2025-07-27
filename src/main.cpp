#include "../include/Window.h"
#include "../include/Input.h"
#include "../include/Camera.h"
#include "../include/Renderer.h"
#include "../include/ObjLoader.h"

#include <Windows.h>
#include <gl/GL.h>
#include <cmath>
#include <assimp/Importer.hpp>






int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
	Window window(hInstance, 800, 600, "3D Sphere + Camera");
	Input input;
	Camera camera;
	Renderer renderer;

	ShowCursor(FALSE);

	float angle = 0.0f;


	while (window.processMessages()) {
		input.update(window.getHWND()); // pass HWND
		camera.update(input);
		renderer.draw(angle, camera);
		SwapBuffers(window.getHDC());

		//angle = fmod(angle + 0.5f, 360.0f);
		
		if (input.keyDown(VK_ESCAPE)) {
			break;  // break out of your game loop
		}


		Sleep(16);


	}

	return 0;
}

