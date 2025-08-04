#ifndef ObjLoader_h
#define ObjLoader_h

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "../include/RenderComponent.h"


#include "../../../../../../Libraries/glm/glm.hpp"


class ObjLoader{



public:

	ObjLoader();
	~ObjLoader();

	void make_obj(glm::vec3 position, glm::vec3 eulers);
	void make_obj_mesh(const char* filename);
	std::vector<std::string> Split(std::string line, std::string delimiter);
	glm::vec2 read_vec2(std::vector<std::string> words);
	glm::vec3 read_vec3(std::vector<std::string> words);
	void read_face(std::vector<std::string> words, std::vector<glm::vec3>& v, std::vector<glm::vec2>& vt, std::vector<glm::vec3>& vn, std::vector<float>& vertices);
	void read_corner(std::string description, std::vector<glm::vec3>& v, std::vector<glm::vec2>& vt, std::vector<glm::vec3>& vn, std::vector<float>& vertices);


	
private:

	

};


#endif /* ObjLoader_h*/
