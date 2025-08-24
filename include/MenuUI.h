#ifndef MenuUI_h
#define MenuUI_h

#include <imgui.h>
#include <glm.hpp>

class MenuUI{



public:

	MenuUI();
	~MenuUI();



	void PauseMenu(float &speed);
	void OtherMenu();
	void SphereColorMenu(glm::vec3* sphereColor);

private:


};


#endif /* MenuUI_h*/
