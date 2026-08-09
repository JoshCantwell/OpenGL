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

	Terrain terrain(
			"C:/Users/joshDope/Documents/cppCode/OpenGL/Assets/Terrain/heightmap2.png",
			200.0f,
			30.0f
		       );

	std::vector<std::string> skyboxFaces =
	{
		"C:/Users/joshDope/Documents/cppCode/OpenGL/Assets/Skybox/Option1/posx.jpg",
		"C:/Users/joshDope/Documents/cppCode/OpenGL/Assets/Skybox/Option1/negx.jpg",
		"C:/Users/joshDope/Documents/cppCode/OpenGL/Assets/Skybox/Option1/posy.jpg",
		"C:/Users/joshDope/Documents/cppCode/OpenGL/Assets/Skybox/Option1/negy.jpg",
		"C:/Users/joshDope/Documents/cppCode/OpenGL/Assets/Skybox/Option1/posz.jpg",
		"C:/Users/joshDope/Documents/cppCode/OpenGL/Assets/Skybox/Option1/negz.jpg"
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



	Model testModel2("C:/Users/joshDope/Documents/cppCode/OpenGL/Assets/GraniteSlab.obj");

	Model testModel3("C:/Users/joshDope/Documents/cppCode/OpenGL/Assets/PlanetaryGear.obj");

	std::vector<RenderObject> sceneObjects;

	RenderObject cube;
	cube.name = "Granite Slab";
	cube.model = &testModel2;
	cube.position = {4.0f, 4.0f, -3.0f};
	cube.rotation = {0.0f, 45.0f, 0.0f};
	cube.scale = {2.0f, 16.0f, 2.0f};
	sceneObjects.push_back(cube);

	RenderObject brick;
	brick.name = "Brick Cylinder";
	brick.model = &testModel;
	brick.position = {0.0f, 1.0f, 0.0f};
	brick.rotation = {0.0f, 45.0f, 0.0f};
	brick.scale = {1.5f, 1.05f, 1.05f};
	sceneObjects.push_back(brick);

	RenderObject gear;
	gear.name = "Planetary Gear";
	gear.model = &testModel3;
	gear.position = {6.0f, 5.0f, 25.0f};
	gear.rotation = {0.0f, 45.0f, 0.0f};
	gear.scale = {0.2f, 0.2f, 0.2f};
	sceneObjects.push_back(gear);


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

			menu.ObjectSpawner(
					sceneObjects,
					testModel,
					testModel2,
					testModel3
					);
			menu.SceneEditor(
					sceneObjects
					);


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
		renderer.drawTerrain(
				terrain,
				camera
				);
		for (const auto& object : sceneObjects)
		{
			renderer.drawObject(
					object,
					camera
					);
		}	

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




