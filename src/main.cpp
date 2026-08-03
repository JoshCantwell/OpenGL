#include <Window.h>
#include <Input.h>
#include <Camera.h>
#include <MenuUI.h>
#include <AudioManager.h>
#include <Renderer.h>
#include <Windows.h>
#include <assimp/Importer.hpp>
#include <MenuUI.h>
#include <backends/imgui_impl_win32.h>
#include <backends/imgui_impl_opengl3.h>
#include <Model.h>
#include <winuser.h>
#include <Shader.h>
#include <Skybox.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {

	constexpr int windowWidth = 1920;
	constexpr int windowHeight = 1080;

	Window window(
			hInstance,
			windowWidth,
			windowHeight,
			"3D Sphere + Camera"
		     );

	Input input;
	Camera camera;
	Renderer renderer;
	AudioManager audioManager;
	MenuUI menu;

	std::vector<std::string> skyboxFaces =
	{
		"C:/Users/joshDope/Documents/cppCode/OpenGL/Assets/Skybox/posx.jpg",
		"C:/Users/joshDope/Documents/cppCode/OpenGL/Assets/Skybox/negx.jpg",
		"C:/Users/joshDope/Documents/cppCode/OpenGL/Assets/Skybox/posy.jpg",
		"C:/Users/joshDope/Documents/cppCode/OpenGL/Assets/Skybox/negy.jpg",
		"C:/Users/joshDope/Documents/cppCode/OpenGL/Assets/Skybox/posz.jpg",
		"C:/Users/joshDope/Documents/cppCode/OpenGL/Assets/Skybox/negz.jpg"
	};

	Skybox skybox(skyboxFaces);




	if (!audioManager.init()) {
		MessageBoxA(nullptr, "Failed to initialize audio", "Error", MB_OK | MB_ICONERROR);
		return -1;
	}	
	audioManager.loadSound("pause", "C:/Users/joshDope/Documents/cppCode/OpenGL/Assets/mysticalfantasyloop.wav");

	bool isPaused = false;

	ShowCursor(FALSE);

	Mix_VolumeMusic(MIX_MAX_VOLUME / 3);	
	float angle = 0.0f;
	float speed = 0.05f;
	float size = 0.0f;

	glm::vec3 sphereColor = glm::vec3(1.0f, 0.0f, 0.0f);


	audioManager.setVolume(MIX_MAX_VOLUME / 100);



	Model testModel("C:/Users/joshDope/Documents/cppCode/OpenGL/Assets/BrickCylinder.obj");

	MessageBoxA(
			nullptr,
			"Gear model constructed",
			"Main Debug",
			MB_OK
		   );


	Model testModel2("C:/Users/joshDope/Documents/cppCode/OpenGL/Assets/GraniteSlab.obj");


	MessageBoxA(
			nullptr,
			"Cube model constructed",
			"Main Debug",
			MB_OK
		   );

	RenderObject cube;
	cube.model = &testModel2;
	cube.position = {4.0f, 4.0f, -3.0f};
	cube.rotation = {0.0f, 45.0f, 0.0f};
	cube.scale = {2.0f, 16.0f, 2.0f};

	RenderObject gear;
	gear.model = &testModel;
	gear.position = {0.0f, 1.0f, 0.0f};
	gear.rotation = {0.0f, 45.0f, 0.0f};
	gear.scale = {1.5f, 1.05f, 1.05f};



	while (window.processMessages()) {

		renderer.updateMovement();
		if (input.keyPressed('P')) {
			isPaused = !isPaused;
			audioManager.playSound("pause");
			ShowCursor(TRUE);
		}


		if(isPaused){
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();




			menu.PauseMenu(speed, size);		
			menu.OtherMenu();

			menu.SphereColorMenu(&sphereColor);
		} else {
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
			menu.ShowDockedPanel(camera);

		}



		glm::vec3 cameraPosition(
				camera.camX,
				camera.camY,
				camera.camZ
				);

		glm::vec3 cameraDirection(
				camera.getDirX(),
				camera.getDirY(),
				camera.getDirZ()
				);

		glm::mat4 view = glm::lookAt(
				cameraPosition,
				cameraPosition + cameraDirection,
				glm::vec3(0.0f, 1.0f, 0.0f)
				);

		glm::mat4 projection = glm::perspective(
				glm::radians(60.0f),
				static_cast<float>(windowWidth) /
				static_cast<float>(windowHeight),
				0.1f,
				500.0f
				);







		input.update(window.getHWND(), isPaused); // pass HWND
		if (isPaused) {
			ShowCursor(TRUE);
			camera.update(input, 0);
		} else {

			ShowCursor(FALSE);
			bool showMyWindow = true; // Controls window visibility
			camera.update(input, speed);  // Only update camera when not paused
		}	
		renderer.draw(angle, camera, sphereColor);
		renderer.drawObject(gear, camera);
		renderer.drawObject(cube, camera);

		skybox.Draw(view, projection);

		//if (isPaused){
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		//}




		SwapBuffers(window.getHDC());


		if (input.keyDown(VK_ESCAPE)) {
			break;  // break out of your game loop
		}


		Sleep(16);


	}

	audioManager.cleanUp();

	return 0;
}




