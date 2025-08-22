#include "MenuUI.h"


MenuUI::MenuUI(){


}

MenuUI::~MenuUI(){


}

void MenuUI::PauseMenu(float &speed) {

	
	ImGui::Begin("Hello, ImGui!");
	ImGui::Text("Lever Position:");
	ImGui::SliderFloat("##lever", &speed, 0.0f, 0.1f, "%.3f");
	// Visual Feedback
	if (speed < 0.05f) {
		ImGui::Text("Lever is Low");
	} else {
		ImGui::Text("Lever is High");
	}

}
