#include <SDL3/SDL.h>
#include <Window.h>
#include <Input.h>
#include <Camera.h>
#include <Renderer.h>
#include <ObjLoader.h>
#include <Windows.h>
#include <gl/GL.h>
#include <cmath>
#include <assimp/Importer.hpp>
#include <imgui.h>
#include <backends/imgui_impl_win32.h>
#include <backends/imgui_impl_opengl3.h>




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {

	if (SDL_Init(SDL_INIT_AUDIO) != 0) {
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	std::cout << "SDL audio initialized successfully!\n";

	Window window(hInstance, 1200, 900, "3D Sphere + Camera");
	Input input;
	Camera camera;
	Renderer renderer;

	bool isPaused = false;

	ShowCursor(FALSE);

	float angle = 0.0f;


	while (window.processMessages()) {

		if (input.keyPressed('P')) {
			isPaused = !isPaused;
		}


		if(isPaused){
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
			ImGui::Begin("Hello, ImGui!");
			ImGui::Text("This is an ImGui window!");
			ImGui::End();

		}

		input.update(window.getHWND(), isPaused); // pass HWND
		if (isPaused) {
			ShowCursor(TRUE);
		} else {
			ShowCursor(FALSE);
			camera.update(input);  // Only update camera when not paused
		}	
		renderer.draw(angle, camera);


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

	SDL_Quit();
	return 0;
}

