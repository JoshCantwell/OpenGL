#ifndef MenuUI_h
#define MenuUI_h

#include <imgui.h>
#include <glm.hpp>
#include <string>
#include <Camera.h>

class MenuUI{



public:

	MenuUI();
	~MenuUI();



	void ShowDockedPanel(Camera camera);
	void PauseMenu(float &speed);
	void OtherMenu();
	void SphereColorMenu(glm::vec3* sphereColor);

private:


};


#endif /* MenuUI_h*/
