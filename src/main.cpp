#include <Window.h>
#include <Input.h>
#include <Camera.h>
#include <MenuUI.h>
#include <AudioManager.h>
#include <Renderer.h>
#include <ObjLoader.h>
#include <Windows.h>
#include <gl/GL.h>
#include <assimp/Importer.hpp>
#include <MenuUI.h>
#include <backends/imgui_impl_win32.h>
#include <backends/imgui_impl_opengl3.h>



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {

	Window window(hInstance, 1200, 900, "3D Sphere + Camera");
	Input input;
	Camera camera;
	Renderer renderer;
	AudioManager audioManager;
	MenuUI menu;

	if (!audioManager.init()) {
		MessageBoxA(nullptr, "Failed to initialize audio", "Error", MB_OK | MB_ICONERROR);
		return -1;
	}	
	audioManager.loadSound("pause", "C:/Users/joshDope/Documents/cppCode/OpenGL/Assets/sound.wav");

	bool isPaused = false;

	ShowCursor(FALSE);

	float angle = 0.0f;
	float speed = 0.05f;

	glm::vec3 sphereColor = glm::vec3(1.0f, 0.0f, 0.0f);


	while (window.processMessages()) {

		if (input.keyPressed('P')) {
			isPaused = !isPaused;
			audioManager.playSound("pause");
		}


		if(isPaused){
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			menu.PauseMenu(speed);		
			menu.OtherMenu();

			menu.SphereColorMenu(&sphereColor);
		}

		input.update(window.getHWND(), isPaused); // pass HWND
		if (isPaused) {
			ShowCursor(TRUE);
			camera.update(input, 0);
		} else {
			ShowCursor(FALSE);
			camera.update(input, speed);  // Only update camera when not paused
		}	
		renderer.draw(angle, camera, sphereColor);


		if (isPaused){
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}




		SwapBuffers(window.getHDC());

		//angle = fmod(angle + 0.5f, 360.0f);

	if (input.keyDown(VK_ESCAPE)) {
			break;  // break out of your game loop
		}


		Sleep(16);


	}

	audioManager.cleanUp();

	return 0;
}

