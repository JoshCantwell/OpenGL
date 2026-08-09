#ifndef MenuUI_h
#define MenuUI_h

#include <imgui.h>
#include <glm.hpp>
#include <string>
#include <Camera.h>
#include <vector>
#include <RenderObject.h>
#include <Model.h>

class MenuUI{



public:

	MenuUI();
	~MenuUI();



	void ShowDockedPanel(Camera camera);
	void PauseMenu(float &speed, float &size);
	void OtherMenu();
	void SphereColorMenu(glm::vec3* sphereColor);

	void ObjectSpawner(
			std::vector<RenderObject>& sceneObjects,
			Model& gearModel,
			Model& cylinderModel,
			Model& graniteCubeModel
			);

	void SceneEditor(
			std::vector<RenderObject>& sceneObjects
			);


private:


};


#endif /* MenuUI_h*/
