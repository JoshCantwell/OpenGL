#include "MenuUI.h"


MenuUI::MenuUI(){


}

MenuUI::~MenuUI(){


}

void MenuUI::ShowDockedPanel(Camera camera) {
	ImVec2 displaySize = ImGui::GetIO().DisplaySize;

	float cameraPositionX = camera.camX;
	float cameraPositionY = camera.camY;
	float cameraPositionZ = camera.camZ;

	float leftPanelWidth = 200.0f;
	float rightPanelWidth = 200.0f;

	ImGuiWindowFlags panelFlags = ImGuiWindowFlags_NoMove |
		//ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoTitleBar;

	// ---- LEFT PANEL ----
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(leftPanelWidth, displaySize.y));
	ImGui::Begin("Left Panel", nullptr, panelFlags);
	ImGui::Text("Camera X Position: %f", cameraPositionX);
	ImGui::Text("Camera Y Position: %f", cameraPositionY);
	ImGui::Text("Camera Z Position: %f", cameraPositionZ);
	ImGui::End();

	// ---- RIGHT PANEL ----
	ImGui::SetNextWindowPos(ImVec2(displaySize.x - rightPanelWidth, 0));
	ImGui::SetNextWindowSize(ImVec2(rightPanelWidth, displaySize.y));
	ImGui::Begin("Right Panel", nullptr, panelFlags);
	ImGui::Text("Right sidebar content");
	ImGui::End(); 
}


void MenuUI::PauseMenu(float &speed) {


	ImGui::Begin("Hello, ImGui!2");
	ImGui::Text("Lever Position:");
	ImGui::SliderFloat("##lever", &speed, 0.0f, 0.1f, "%.3f");
	// Visual Feedback
	if (speed < 0.05f) {
		ImGui::Text("Lever is Low");
	} else {
		ImGui::Text("Lever is High");
	}


	ImGui::End();
}


void MenuUI::OtherMenu() {

	float speed;	
	ImGui::Begin("Hello, ImGui!");
	ImGui::Text("Lever Position:");
	// Visual Feedback
	if (speed < 0.05f) {
		ImGui::Text("Lever is Low");
	} else {
		ImGui::Text("Lever is High");
	}

	ImGui::End();
}

void MenuUI::SphereColorMenu(glm::vec3* sphereColor) {

	ImGui::Begin("Sphere Settings");

	// Conver glm::vec3 to float array (ImGui wants an array)
	float color[3] = { sphereColor->r, sphereColor->g, sphereColor->b };

	if (ImGui::ColorEdit3("Sphere Color", color)) {

		*sphereColor = glm::vec3(color[0], color[1], color[2]);
	}

	ImGui::End();
}
