#include "MenuUI.h"


MenuUI::MenuUI(){


}

MenuUI::~MenuUI(){


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
