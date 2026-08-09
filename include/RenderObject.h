#pragma once

#include <Model.h>
#include <glm/glm.hpp>
#include <string>

struct RenderObject
{

	std::string name = "Object";
	Model* model = nullptr;

	glm::vec3 position = {0.0f, 0.0f, 0.0f};
	glm::vec3 rotation = {0.0f, 0.0f, 0.0f}; // degrees
	glm::vec3 scale    = {1.0f, 1.0f, 1.0f};
};
