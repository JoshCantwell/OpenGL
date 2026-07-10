#pragma once
#include "Camera.h"
#include <Model.h>
#include <glm.hpp>
#include <RenderObject.h>
#include <Shader.h>

class Renderer {
	public:
		Renderer();
		~Renderer();

		void updateMovement();

		void drawObject(const RenderObject& object, const Camera& camera);
		void draw(float angle, const class Camera& camera, const glm::vec3& sphereColor);
	private:
		struct GLUquadric* quad;

		Shader modelShader;

		float i = 3;
		float playerY = 0;
		float playerZ = -5;



};

