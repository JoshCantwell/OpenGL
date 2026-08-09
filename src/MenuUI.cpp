#include "MenuUI.h"


MenuUI::MenuUI(){


}

MenuUI::~MenuUI(){


}

void MenuUI::SceneEditor(
		std::vector<RenderObject>& sceneObjects)
{
	ImGui::Begin("Scene Objects");

	static int selectedObject = -1;

	// -------------------------
	// Object list
	// -------------------------
	ImGui::Text("Objects in Scene");

	ImGui::Separator();

	for (int i = 0;
			i < static_cast<int>(sceneObjects.size());
			++i)
	{
		
		std::string label =
			sceneObjects[i].name +
			"##" +
			std::to_string(i);	
	

		bool selected =
			selectedObject == i;

		if (ImGui::Selectable(
					label.c_str(),
					selected))
		{
			selectedObject = i;
		}
	}

	ImGui::Separator();

	// -------------------------
	// Selected object editor
	// -------------------------
	if (selectedObject >= 0 &&
			selectedObject <
			static_cast<int>(sceneObjects.size()))
	{
		RenderObject& object =
			sceneObjects[selectedObject];

		ImGui::Text(
				"Editing Object %d",
				selectedObject
			   );

		ImGui::Separator();

		ImGui::DragFloat3(
				"Position",
				&object.position.x,
				0.1f
				);

		ImGui::DragFloat3(
				"Rotation",
				&object.rotation.x,
				1.0f
				);

		ImGui::DragFloat3(
				"Scale",
				&object.scale.x,
				0.05f,
				0.01f,
				100.0f
				);

		ImGui::Separator();

		if (ImGui::Button("Duplicate Object"))
		{
			RenderObject copy = object;

			// Offset it slightly so it isn't directly
			// inside the original.
			copy.position.x += 2.0f;

			sceneObjects.push_back(copy);
		}

		ImGui::SameLine();

		if (ImGui::Button("Delete Object"))
		{
			sceneObjects.erase(
					sceneObjects.begin() +
					selectedObject
					);

			selectedObject = -1;
		}
	}
	else
	{
		ImGui::Text(
				"Select an object to edit."
			   );
	}

	ImGui::End();
}

void MenuUI::ObjectSpawner(
		std::vector<RenderObject>& sceneObjects,
		Model& gearModel,
		Model& cylinderModel,
		Model& graniteCubeModel)
{
	ImGui::Begin("Add Object");

	static int selectedModel = 0;

	static float position[3] =
	{
		0.0f,
		0.0f,
		0.0f
	};

	static float rotation[3] =
	{
		0.0f,
		0.0f,
		0.0f
	};

	static float scale[3] =
	{
		1.0f,
		1.0f,
		1.0f
	};

	static char objectName[64] = "New Object";

	const char* modelNames[] =
	{
		"Brick Cylinder",
		"Granite Slab",
		"Planetary Gear"
	};

	ImGui::Combo(
			"Model",
			&selectedModel,
			modelNames,
			IM_ARRAYSIZE(modelNames)
		    );

	ImGui::InputText(
			"Object Name",
			objectName,
			IM_ARRAYSIZE(objectName)
			);

	ImGui::DragFloat3(
			"Position",
			position,
			0.1f
			);

	ImGui::DragFloat3(
			"Rotation",
			rotation,
			1.0f
			);

	ImGui::DragFloat3(
			"Scale",
			scale,
			0.05f,
			0.01f,
			100.0f
			);

	if (ImGui::Button("Add Object"))
	{
		RenderObject object;

		object.name = objectName;

		switch (selectedModel)
		{
			case 0:
				object.model = &gearModel;
				break;

			case 1:
				object.model = &cylinderModel;
				break;

			case 2:
				object.model = &graniteCubeModel;
				break;
		}

		object.position =
		{
			position[0],
			position[1],
			position[2]
		};

		object.rotation =
		{
			rotation[0],
			rotation[1],
			rotation[2]
		};

		object.scale =
		{
			scale[0],
			scale[1],
			scale[2]
		};

		sceneObjects.push_back(object);

		// Reset for the next object
		strcpy(objectName, "New Object");

		position[0] = position[1] = position[2] = 0.0f;

		rotation[0] = rotation[1] = rotation[2] = 0.0f;

		scale[0] = scale[1] = scale[2] = 1.0f;
	}

	ImGui::End();
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


void MenuUI::PauseMenu(float &speed, float &size) {

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


	ImGui::Begin("Hello, ImGui!3");
	ImGui::Text("Lever Position:");
	ImGui::SliderFloat("##lever", &size, 0.0f,0.1f, "%.3f");
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
